#include "ResourcePackage.hpp"

#include "common/star/tarlib.hpp"

#include <format.h>

namespace client {

ResourcePackage::ResourcePackage(std::string path, PackageType type)
                                 : m_name(path), m_type(type) {
    Tar tar(path);
    std::string manifest, error;
    for (TarEntry * e : tar.getEntries()) {
        // Look for the manifest.
        if (std::string(e->name) == "manifest") {
            manifest = e->contents;
        }
    }

    if (manifest == std::string()) {
        throw std::runtime_error("Manifest file was not found (or empty)!\n");
    }

    json11::Json json;
    json = json11::Json::parse(manifest, error);

    if (!error.empty()) {
        throw std::runtime_error(
            fmt::format("Error while parsing resource package manifest {}!\n"
                        "JSON error: {}\n", path, error)
        );
    }

    m_manifest = json;
}

std::string ResourcePackage::getName() { return m_name; }
PackageType ResourcePackage::getType() { return m_type; }

std::vector<json11::Json> ResourcePackage::getJsonManifest() {
    return m_manifest.array_items();
}

}