#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\FixedArrayRef.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
    [TestClass]
    public ref class FixedArrayRefTest
    {
        static const int MagicNumber = 42;

    public: 
        [TestMethod]
        void ArrayRef_IsValidIndex_InvalidIndex_False()
        {
            int array[2] = {};
            FixedArrayRef<int, 2> tested(array);

            Assert::IsFalse(tested.IsValidIndex(2));
        }

        [TestMethod]
        void ArrayRef_GetAt_InvalidIndex_DefaultInt()
        {
            int array[2] = {};
            FixedArrayRef<int, 2> tested(array);

            Assert::AreEqual(0, tested.GetAt(2));
        }

        [TestMethod]
        void ArrayRef_SetAt_ValidIndexAndValue_GetAtRetrieves()
        {
            const unsigned char testIndex = 0;
            int array[2] = {};
            FixedArrayRef<int, 2> tested(array);

            tested.SetAt(testIndex, MagicNumber);

            Assert::AreEqual(MagicNumber, tested.GetAt(testIndex));
        }
    };
}
