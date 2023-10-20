namespace engine
{
    namespace core
    {
        class CPePointerSorter
        {
        public:
            template<typename T>
            bool operator()(T* a, T* b)
            {
                return (*a) > (*b);
            }
        };
    }
}

