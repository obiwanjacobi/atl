#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Array.h"
#include "..\ArduinoTemplateLibrary\ArrayRef.h"
#include "..\ArduinoTemplateLibrary\Collection.h"
#include "..\ArduinoTemplateLibrary\CollectionRef.h"
#include "..\ArduinoTemplateLibrary\FixedArray.h"
#include "..\ArduinoTemplateLibrary\FixedArrayRef.h"
#include "..\ArduinoTemplateLibrary\FixedString.h"
//#include "..\ArduinoTemplateLibrary\StaticArray.h"    // problems with ProgMemAccessor

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
    template<typename ArrayT>
    class ReadOnlyArrayInterfaceTest : public ArrayT
    {
    public:
        typedef typename ArrayT::ItemT ItemT;

        ReadOnlyArrayInterfaceTest()
        {}

        ReadOnlyArrayInterfaceTest(ItemT* array)
            : ArrayT(array)
        { }

        inline void CallAllInterfaceMethods()
        {
            uint16_t capacity = ArrayT::getCapacity();
            uint16_t count = ArrayT::getCount();
            ItemT item0 = ArrayT::GetAt(0);
            ItemT* pBuffer = ArrayT::getBuffer();
            bool validIndex = ArrayT::IsValidIndex(0);
            int16_t index = ArrayT::IndexOf(0);
        }
    };

    template<typename ArrayT>
    class WritableArrayInterfaceTest : public ReadOnlyArrayInterfaceTest<ArrayT>
    {
    public:
        typedef typename ArrayT::ItemT ItemT;

        WritableArrayInterfaceTest()
        { }

        WritableArrayInterfaceTest(ItemT* array)
            : ReadOnlyArrayInterfaceTest<ArrayT>(array)
        { }

        inline void CallAllInterfaceMethods()
        {
            ReadOnlyArrayInterfaceTest<ArrayT>::CallAllInterfaceMethods();

            ArrayT::Clear();
            ArrayT::SetAt(0, 0);
        }

    };

	[TestClass]
	public ref class ArrayTest
	{
	public: 
		[TestMethod]
        [TestCategory("CompilerTest")]
		void Array_ReadOnlyInterface_Test()
		{
            ReadOnlyArrayInterfaceTest<Array<uint8_t, 2> > array;
            array.CallAllInterfaceMethods();
            
            WritableArrayInterfaceTest<FixedArray<uint8_t, 2> > fixedArray;
            fixedArray.CallAllInterfaceMethods();

            WritableArrayInterfaceTest<FixedString<2> > fixedString;
            fixedString.CallAllInterfaceMethods();

            // Array Refs

            uint8_t nakedArray[2] = {};

            ReadOnlyArrayInterfaceTest<ArrayRef<uint8_t, 2> > arrayRef(nakedArray);
            arrayRef.CallAllInterfaceMethods();

            WritableArrayInterfaceTest<FixedArrayRef<uint8_t, 2> > fixedArrayRef(nakedArray);
            fixedArrayRef.CallAllInterfaceMethods();
		}

        [TestMethod]
        [TestCategory("CompilerTest")]
        void Collection_ReadOnlyInterface_Test()
        {
            ReadOnlyArrayInterfaceTest<Collection<Array<uint8_t, 2> > > array;
            array.CallAllInterfaceMethods();

            WritableArrayInterfaceTest<Collection<FixedArray<uint8_t, 2> > > fixedArray;
            fixedArray.CallAllInterfaceMethods();

            WritableArrayInterfaceTest<Collection<FixedString<2> > > fixedString;
            fixedString.CallAllInterfaceMethods();

            // Array Refs

            uint8_t nakedArray[2] = {};

            ReadOnlyArrayInterfaceTest<Collection<ArrayRef<uint8_t, 2> > > arrayRef(nakedArray);
            arrayRef.CallAllInterfaceMethods();

            WritableArrayInterfaceTest<Collection<FixedArrayRef<uint8_t, 2> > > fixedArrayRef(nakedArray);
            fixedArrayRef.CallAllInterfaceMethods();
        }
	};
}
