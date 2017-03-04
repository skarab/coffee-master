namespace unit_test
{
    TDOG_TEST_SUITE(CorePlatform)
    {
        TDOG_TEST_CASE(GetTime)
        {
            TDOG_ASSERT(coffee::core::Platform::Get().GetTime()>0.0f);
            TDOG_ASSERT(coffee::core::Platform::Get().GetTime()<60.0f);
        }
    }
}
