typedef int Rank;
constexpr auto DEFAULT_CAPACITY = 3;

template<typename T>
class vectorJS {
private:
    Rank _size; int _capacity; T* _elem;

    void copyFrom(T const* A, Rank lo, Rank hi) {
        _elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;
        while (lo < hi)
            _elem[_size++] = A[lo++];
    }

    void merge(Rank lo, Rank mi, Rank hi) {
        T* A = _elem + lo;
        int lb = mi - lo; T* B = new T[lb];
        for (Rank i = 0; i < lb; B[i] = A[i++]);
        int lc = hi - mi; T* C = _elem + mi;
        for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) {
            if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
            if ((k < lc) && (!(j < lb) || (C[k] < B[j]))) A[i++] = C[k++];
        }
        delete[]B;
    }
    void mergeSort(Rank lo, Rank hi) {
        if (hi - lo < 2) {
            return;
        }
        int mi = (lo + hi) >> 1;
        mergeSort(lo, mi); mergeSort(mi, hi); merge(lo, mi, hi);
    }

public:
    vectorJS(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }
    vectorJS(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    vectorJS(T const* A, Rank n) { copyFrom(A, 0, n); }
    vectorJS(vectorJS<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }
    vectorJS(vectorJS<T> const& V) { copyFrom(V._elem, 0, V._size); }

    ~vectorJS() { delete[] _elem; }

    Rank size() const { return _size; }

    T& operator[](Rank r) const;
    vectorJS<T>& operator=(vectorJS<T> const&);

    void traverse(void (*visit)(T&)) {
        for (int i = 0; i < _size; i++) {
            visit(_elem[i]);
        }
    }
    template <typename VST>
    void traverse(VST& visit) {
        for (int i = 0; i < _size; i++) {
            visit(_elem[i]);
        }
    }

};

template <typename T>
T& vectorJS<T>::operator[](Rank r) const { return _elem[r]; }

template <typename T>
vectorJS<T>& vectorJS<T>::operator=(vectorJS<T> const& V) {
    if (_elem) delete[] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template <typename T>
struct Show {
    virtual void operator()(T& e) {
        std::cout << e << ", ";
    }
};

template <typename T>
void showElements(vectorJS<T>& V) {
    /*
        遍历输出vector V的值
    */
    std::cout << '[';
    Show<T> a;
    V.traverse(a);
    std::cout << ']' << std::endl;
}