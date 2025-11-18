// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


typedef signed char __int8_t;
typedef int BOOL;
class CMsgAgent;

class CFs {
public:
  typedef enum {} CACHE_HINT;
  virtual BOOL ReqCacheHint( CMsgAgent* p_ma, CACHE_HINT hint, ... ) ;
};

typedef struct {} _Lldiv_t;

class CBdVfs {
public:
  virtual ~CBdVfs( ) {}
};

class CBdVfsImpl : public CBdVfs, public CFs {
  BOOL ReqCacheHint( CMsgAgent* p_ma, CACHE_HINT hint, ... );
};

BOOL CBdVfsImpl::ReqCacheHint( CMsgAgent* p_ma, CACHE_HINT hint, ... ) {
  return true;
}

