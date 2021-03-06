#ifndef MPD_CONTROL_HPP
#define MPD_CONTROL_HPP

#include <functional>
#include <mutex>
#include <queue>
#include <future>
#include <optional>

#include <mpd/client.h>

#if defined(HAVE_POLL_H) && defined(HAVE_SYS_EVENTFD_H) && defined(HAVE_UNISTD_H)
#pragma message ( "Compiling with eventfd polling support." )
#define USE_POLL
#endif

struct playlist_change_info
{
    typedef std::vector<std::pair<unsigned int, std::string>> diff_type;

    playlist_change_info(int nv, diff_type && cp, unsigned int l);

    unsigned int new_version;
    diff_type changed_positions;
    unsigned int new_length;
};

struct song_location
{
    std::string path;
    unsigned int pos;
};

struct status_info
{
};

struct mpd_control
{
    mpd_control
        ( std::function<void(std::optional<song_location>)> new_song_cb
        , std::function<void(bool)> random_cb
        , std::function<void()> playlist_changed_cb
        );
    ~mpd_control();

    void run();

    void stop();
    void toggle_pause();
    void inc_volume(unsigned int amount);
    void dec_volume(unsigned int amount);
    void next_song();
    void prev_song();

    void play_position(int pos);

    void set_random(bool value);

    bool get_random();

    std::string get_current_title();
    std::string get_current_artist();
    std::string get_current_album();

    std::pair<std::vector<std::string>, unsigned int> get_current_playlist();

    playlist_change_info get_current_playlist_changes(unsigned int version);

    private:

    std::string get_current_tag(enum mpd_tag_type type);

    void add_external_task(std::function<void(mpd_connection *)> t);

    template <typename R>
    R add_external_task_with_return(std::function<R(mpd_connection *)> f)
    {
        auto promise_ptr = std::make_shared<std::promise<R>>();
        add_external_task([promise_ptr, f](mpd_connection * c)
        {
            promise_ptr->set_value(f(c));
        });
        return promise_ptr->get_future().get();
    }

    void new_song_cb(mpd_song * s);

    mpd_connection * _c;

    bool _run;

    std::function<void(std::optional<song_location>)> _new_song_cb;
    std::function<void(bool)> _random_cb;
    std::function<void()> _playlist_changed_cb;

    std::mutex _external_tasks_mutex;
    std::deque<std::function<void(mpd_connection *)>> _external_tasks;

    std::mutex _external_song_queries_mutex;
    std::deque<std::function<void(mpd_connection *, mpd_song *)>> _external_song_queries;

#ifdef USE_POLL
    // a file descriptor for thread communication
    int _eventfd;
#endif
};

#endif

