/*!
 * \author ddubois 
 * \date 16-Feb-18.
 */

#ifndef VIEWER_DATA_STORE_H
#define VIEWER_DATA_STORE_H

#include <cstdint>
#include <queue>
#include <mutex>
#include <unordered_map>

namespace viewer {
    /*!
     * \brief Template class to represent a thing that receives data from UGE and has that data added to things on a
     * separate thread
     *
     * \tparam stored_type The type of the object that this class stores
     */
    template<typename stored_type>
    class data_transfer_point {
    public:
        /*!
         * \brief Goes through the queue of objects, adding each one to the thread-local storage
         *
         * This method will often upload the object to the GPU while maintaining
         */
        virtual void process_new_objects() = 0;

        void add_object(uint32_t key, stored_type data_to_store) {
            new_objects_lock.lock();
            new_objects.push(std::pair<uint32_t, stored_type>{key, data_to_store});
            new_objects_lock.unlock();
        }

    protected:
        std::queue<std::pair<uint32_t, stored_type>> new_objects;
        std::mutex new_objects_lock;
    };
}


#endif //VIEWER_DATA_STORE_H
