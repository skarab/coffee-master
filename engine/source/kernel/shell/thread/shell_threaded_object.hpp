//------------------------------------------------------------------------------------------------//
/// @file kernel/shell/thread/shell_threaded_object.hpp
//------------------------------------------------------------------------------------------------//

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< class type >
    ThreadedObject< type >::ThreadedObject() :
        _ItIsLocked(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< class type >
    ThreadedObject< type >::~ThreadedObject()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< class type >
    const type& ThreadedObject< type >::Get() const
    {
        COFFEE_Assert(_ItIsLocked, core::ERROR_CODE_Thread, "Trying to access unlocked object.");
        return _Object;
    }

    //--------------------------------------------------------------------------------------------//

    template< class type >
    type& ThreadedObject< type >::Get()
    {
        COFFEE_Assert(_ItIsLocked, core::ERROR_CODE_Thread, "Trying to access unlocked object.");
        return _Object;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< class type >
    void ThreadedObject< type >::Lock()
    {
        _Mutex.Lock();
        _ItIsLocked = true;
    }

    //--------------------------------------------------------------------------------------------//

    template< class type >
    void ThreadedObject< type >::Unlock()
    {
        _ItIsLocked = false;
        _Mutex.Unlock();
    }

//------------------------------------------------------------------------------------------------//
