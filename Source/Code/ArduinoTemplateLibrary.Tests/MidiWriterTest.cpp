#include "stdafx.h"
#include "TestStream.h"
#include "..\ArduinoTemplateLibrary\MidiMessage.h"
#include "..\ArduinoTemplateLibrary\MidiWriter.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class MidiWriterTest
	{
	public: 
		[TestMethod]
		void InitWithChannelMessage_Write_OutputsToStream()
		{
			MidiMessage midiMsg;
			midiMsg.SetStatusByte(Midi::NoteOn | 1);
			midiMsg.SetDataByte1(64);
			midiMsg.SetDataByte2(100);

			unsigned char buffer[] = { 0x00, 0x00, 0x00, 0x00 };
			MidiWriter<TestStream> target;
			target.InitStream(buffer, 3);

			target.Write(&midiMsg);

			Assert::AreEqual(Midi::NoteOn | 1, (int)buffer[0]);
			Assert::AreEqual(64, (int)buffer[1]);
			Assert::AreEqual(100, (int)buffer[2]);
			Assert::AreEqual(0, (int)buffer[3], "Buffer overrun");
		}
	};
}