#pragma once

#include <xlite/Config.hpp>
#include <xlite/oal/Source.hpp>

#include <cstddef>
#include <memory>
#include <queue>
#include <vector>

#pragma warning(push)
#pragma warning(disable : 4251)// Template warnings on vector/queue private members
namespace Lite {

    namespace Sound {

        class LITE_API Pool {
        public:
            Pool();
            ~Pool() = default;

            std::shared_ptr<Source> Fetch();

            inline size_t Size() const {
                return sources.size();
            }

        private:
            std::vector<std::shared_ptr<Source>> sources;
            std::vector<std::shared_ptr<Source>> acquired;
            std::queue<std::shared_ptr<Source>> available;

            void Update();
        };

    }// namespace Sound

}// namespace Lite
#pragma warning(pop)
