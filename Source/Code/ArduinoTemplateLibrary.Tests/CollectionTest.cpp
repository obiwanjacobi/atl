#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\FixedArray.h"
#include "..\ArduinoTemplateLibrary\Collection.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
    [TestClass]
    public ref class CollectionTest
    {
        typedef Collection<FixedArray<int, 2> > TestCollection;

        static const int MagicNumber = 42;

    public:
        [TestMethod]
        void Count_InitializedCollection_Zero()
        {
            TestCollection tested;

            Assert::AreEqual((int)0, (int)tested.getCount());
        }

        [TestMethod]
        void Count_OneItem_One()
        {
            TestCollection tested;

            tested.Add(0);

            Assert::AreEqual((int)1, (int)tested.getCount());
        }

        [TestMethod]
        void IsValidIndex_InvalidIndex_False()
        {
            TestCollection tested;

            Assert::IsFalse(tested.IsValidIndex(0));
        }

        [TestMethod]
        void IsValidIndex_ValidIndex_True()
        {
            TestCollection tested;

            tested.Add(0);

            Assert::IsTrue(tested.IsValidIndex(0));
        }

        [TestMethod]
        void GetAt_InvalidIndex_DefaultOfT()
        {
            TestCollection tested;

            Assert::AreEqual(Default<int>::DefaultOfT, tested.GetAt(0));
        }

        [TestMethod]
        void GetAt_ValidIndex_Value()
        {
            TestCollection tested;

            tested.Add(MagicNumber);

            Assert::AreEqual(MagicNumber, tested.GetAt(0));
        }

        [TestMethod]
        void Add_TooManyTimes_DoesNotCrash()
        {
            TestCollection tested;

            for (int i = 0; i < 10; i++)
            {
                tested.Add(MagicNumber);
            }

            Assert::AreEqual(tested.getCapacity(), tested.getCount());
        }
    };
}
