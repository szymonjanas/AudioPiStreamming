#pragma once

class Music_controller
{

public:
    Music_controller();
    virtual ~Music_controller();

    virtual void play_music() = 0;
    virtual void pause_music() = 0;
    virtual void stop_music() = 0;
    virtual void set_file_location(const char *) = 0;

};



