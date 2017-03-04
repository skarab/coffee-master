
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename resource_object >
    Handler< resource_object >::Handler() :
        _Resource(NULL),
        _State(HANDLER_STATE_Null),
        _Stamp(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename resource_object >
    Handler< resource_object >::Handler(resource_object* resource) :
        _Resource(resource),
        _State(HANDLER_STATE_Loading),
        _Stamp(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename resource_object >
    Handler< resource_object >::~Handler()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    template< typename resource_object >
    Handler<resource_object>& Handler<resource_object>::operator = (const Handler<resource_object>& other)
    {
        Set(other._Resource);
        return *this;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< typename resource_object >
    void Handler<resource_object>::Set(resource_object* resource)
    {
        _Resource = resource;
        _State = _Resource==NULL?HANDLER_STATE_Null:HANDLER_STATE_Loading;
        _Stamp = 0;
    }
    
    //--------------------------------------------------------------------------------------------//

    template< typename resource_object >
    const resource_object& Handler<resource_object>::Get() const
    {
        COFFEE_Assert(_Resource!=NULL, core::ERROR_CODE_IncorrectUsage, "Check status before!");
        return *_Resource;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename resource_object >
    resource_object& Handler<resource_object>::Get()
    {
        COFFEE_Assert(_Resource!=NULL, core::ERROR_CODE_IncorrectUsage, "Check status before!");
        return *_Resource;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename resource_object >
    HANDLER_STATE Handler<resource_object>::GetState() const
    {
        return _State;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< typename resource_object >
    HANDLER_STATE Handler<resource_object>::Update()
    {
        switch(_State)
        {
            case HANDLER_STATE_BeginLoading:
            {
                _State = HANDLER_STATE_Loading;
            }

            case HANDLER_STATE_Loading:
            {
                if (_Resource->GetChunk().IsLoaded() && _Resource->IsAvailable())
                {
                    _State = HANDLER_STATE_EndLoading;
                    _Stamp = _Resource->GetStamp();
                }
                else if (_Resource->GetChunk().IsInvalid())
                {
                    _State = HANDLER_STATE_Invalid;
                    _Stamp = _Resource->GetStamp();
                }
            } break;

            case HANDLER_STATE_EndLoading:
            {
                _State = HANDLER_STATE_Ready;
            }

            case HANDLER_STATE_Ready:
            case HANDLER_STATE_Invalid:
            {
                if (_Stamp!=_Resource->GetStamp())
                    _State = HANDLER_STATE_BeginLoading;
            } break;

            default:
                break;
        }

        return _State;
    }
