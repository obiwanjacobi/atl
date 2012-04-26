#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\MidiMessage.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class MidiMessageTest
	{
	public: 
		[TestMethod]
		void TestStructureDefinition()
		{
			MidiMessage msg;
			msg.MessageType = Midi::NoteOn;

		}
	};
}
