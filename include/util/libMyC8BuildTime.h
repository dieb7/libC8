#ifndef D_libMyC8BuildTime_H
#define D_libMyC8BuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  libMyC8BuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class libMyC8BuildTime
  {
  public:
    explicit libMyC8BuildTime();
    virtual ~libMyC8BuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    libMyC8BuildTime(const libMyC8BuildTime&);
    libMyC8BuildTime& operator=(const libMyC8BuildTime&);

  };

#endif  // D_libMyC8BuildTime_H
