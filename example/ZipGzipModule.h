#ifndef _ZIP_GZIPMODULE_H_
#define _ZIP_GZIPMODULE_H_

#include <libta/zip/ZipModule.h>
#include <zlib.h>

namespace ta {

class ZipGzipModule : public ZipModule {
public:
    virtual bool compress(const std::string& source, std::string& compressedData, int level = -1);
    virtual bool uncompress(const std::string& compressedData, std::string& source);
    bool build_config(const TAModuleConfig* config);

private:
    int level;
};

} /* namespace ta*/

#endif /* _ZIP_GZIPMODULE_H_ */
