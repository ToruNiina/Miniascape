#ifndef MINIASCAPE_SDL_EXCEPTION
#define MINIASCAPE_SDL_EXCEPTION
#include <stdexcept>
#include <string>

namespace sdl
{

class Exception : public std::exception
{
  public:
    Exception() = default;
    virtual ~Exception() noexcept override = default;

    virtual const char* what() const noexcept override {return "";}
};

class InitError : public Exception
{
  public:
    InitError(const std::string& mes) : mes_(mes){}
    virtual ~InitError() noexcept override = default;

    virtual const char* what() const noexcept override {return mes_.c_str();}

  protected:
    const std::string mes_;
};

class WindowError : public Exception
{
  public:
    WindowError(const std::string& mes) : mes_(mes){}
    virtual ~WindowError() noexcept override = default;

    virtual const char* what() const noexcept override {return mes_.c_str();}
  protected:
    const std::string mes_;
};

class RendererError : public Exception
{
  public:
    RendererError(const std::string& mes) : mes_(mes){}
    virtual ~RendererError() noexcept override = default;

    virtual const char* what() const noexcept override {return mes_.c_str();}
  protected:
    const std::string mes_;
};

}//sdl

#endif /* MINIASCAPE_SDL_EXCEPTION */
