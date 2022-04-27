#ifndef LA_LIBRARY_MT_H
#define LA_LIBRARY_MT_H

template<typename T> void mt_assign(int thread_num, int delta, int size, const std::vector<T>& from,
        std::vector<T>& to) {
    for (int i=thread_num; i<size; i+= delta) {
        to[i] = from[i];
    }
}

template<typename T, typename S> void mt_add(int thread_num, int delta, int size, const std::vector<S>& vc,
        const std::vector<T>& vector, std::vector<S>& res) {
    for (int i=thread_num; i<size; i+= delta) {
        res[i] = vc[i] + vector[i];
    }
}

template<typename T, typename S> void mt_sub(int thread_num, int delta, int size, const std::vector<S>& vc,
                                             const std::vector<T>& vector, std::vector<S>& res) {
    for (int i=thread_num; i<size; i+= delta) {
        res[i] = vector[i] - vc[i];
    }
}

template<typename T, typename S> void mt_com(int thread_num, int delta, int size, const std::vector<S>& vc,
                                             const std::vector<T>& vector, std::atomic<int>& flag) {
    for (int i=thread_num; i<size; i+= delta) {
        if (vector[i] != vc[i]) {
            flag = 0;
            return;
        }
        flag = flag * 2;
    }
}

#endif //LA_LIBRARY_MT_H
