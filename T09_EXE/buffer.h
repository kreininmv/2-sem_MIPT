#ifndef  __BUF__
#define  __BUF__

namespace mk5 {
  struct buffer {
  public:

    size_t size;
    char* buf;

    buffer(void);

    buffer(size_t size, char init = 0);

    buffer(buffer&& buf);

    buffer(const buffer& buf) = delete;

    void fill(const char filename[]);

    bool put(const char filename[]);

    char& operator[] (size_t index);


    ~buffer(void);
  };
}
#endif 
