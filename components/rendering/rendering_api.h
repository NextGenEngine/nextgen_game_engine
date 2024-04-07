#ifndef NEXTGEN_ENGINE_RENDERING_API_H
#define NEXTGEN_ENGINE_RENDERING_API_H

class IRenderingApi {
 public:
  virtual void render() = 0;

  IRenderingApi() = default;
  virtual ~IRenderingApi() = 0;

 protected:
  //  -- Assignment --
  IRenderingApi& operator=(const IRenderingApi&) = default;
  IRenderingApi& operator=(IRenderingApi&&) = default;
  IRenderingApi(const IRenderingApi&) = default;
  IRenderingApi(IRenderingApi&&) = default;
};

#endif
