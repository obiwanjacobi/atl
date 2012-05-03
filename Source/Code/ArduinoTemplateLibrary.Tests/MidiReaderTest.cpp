#include "stdafx.h"
#include "TestStream.h"
#include "..\ArduinoTemplateLibrary\MidiMessage.h"
#include "..\ArduinoTemplateLibrary\MidiReader.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ArduinoTemplateLibraryTests
{
	// helper class that implements Midi events.
	public class MidiReaderBase : public TestStream
	{
	public:
		MidiReaderBase()
		{
			MidiMsg = NULL;
			RealtimeStatus = Midi::InvalidType;
		}

		void OnMessage(MidiMessage* midiMsg)
		{
			MidiMsg = midiMsg;
		}

		MidiMessage* MidiMsg;

		void OnRealtime(Midi::MessageTypes midiStatus)
		{
			RealtimeStatus = midiStatus;
		}

		Midi::MessageTypes RealtimeStatus;

		void OnSysEx(void* obj)
		{
			// not implemented yet
			Assert::Fail("SysEx is not implemented yet!");
		}
	};

	[TestClass]
	public ref class MidiReaderTest
	{
	public: 
		[TestMethod]
		void InitBufferWithNoteOn_Read_FiresChannelMessageEvent()
		{
			MidiReader<MidiReaderBase> midiReader;

			unsigned char buffer[] = { 0x91, 0x40, 0x70 };
			midiReader.InitStream(buffer, 3);

			while(midiReader.Read());

			Assert::IsTrue(midiReader.MidiMsg != NULL);
			Assert::AreEqual((int)Midi::NoteOn, (int)midiReader.MidiMsg->MessageType);
			Assert::AreEqual((unsigned char)1, midiReader.MidiMsg->Channel);
			Assert::AreEqual((unsigned char)0x40, midiReader.MidiMsg->Note);
			Assert::AreEqual((unsigned char)0x70, midiReader.MidiMsg->Velocity);
		}

		[TestMethod]
		void InitBufferWithChannelAndRealtime_Read_FiresChannelMessageAndRealtimeEvent()
		{
			MidiReader<MidiReaderBase> midiReader;

			unsigned char buffer[] = { 0x91, 0x40, 0xFF, 0x70 };
			midiReader.InitStream(buffer, 4);

			while(midiReader.Read());

			Assert::IsTrue(midiReader.MidiMsg != NULL);
			Assert::AreEqual((int)Midi::NoteOn, (int)midiReader.MidiMsg->MessageType);
			Assert::AreEqual((unsigned char)1, midiReader.MidiMsg->Channel);
			Assert::AreEqual((unsigned char)0x40, midiReader.MidiMsg->Note);
			Assert::AreEqual((unsigned char)0x70, midiReader.MidiMsg->Velocity);

			// realtime interleaved midi message
			Assert::AreEqual((int)Midi::SystemReset, (int)midiReader.RealtimeStatus);
		}

		[TestMethod]
		void InitBufferWithMultipleChannelMessages_Read_FiresChannelMessageEvents()
		{
			MidiReader<MidiReaderBase> midiReader;

			unsigned char buffer[] = { 0x91, 0x40, 0x70, 0x81, 0x44, 0x68  };
			midiReader.InitStream(buffer, 6);

			for(int i = 0; i < 3; i++)
				Assert::IsTrue(midiReader.Read());

			Assert::IsTrue(midiReader.MidiMsg != NULL);
			Assert::AreEqual((int)Midi::NoteOn, (int)midiReader.MidiMsg->MessageType);
			Assert::AreEqual((unsigned char)1, midiReader.MidiMsg->Channel);
			Assert::AreEqual((unsigned char)0x40, midiReader.MidiMsg->Note);
			Assert::AreEqual((unsigned char)0x70, midiReader.MidiMsg->Velocity);

			for(int i = 0; i < 3; i++)
				Assert::IsTrue(midiReader.Read());

			Assert::IsTrue(midiReader.MidiMsg != NULL);
			Assert::AreEqual((int)Midi::NoteOff, (int)midiReader.MidiMsg->MessageType);
			Assert::AreEqual((unsigned char)1, midiReader.MidiMsg->Channel);
			Assert::AreEqual((unsigned char)0x44, midiReader.MidiMsg->Note);
			Assert::AreEqual((unsigned char)0x68, midiReader.MidiMsg->Velocity);
		}

		[TestMethod]
		void InitBufferWithRunningStatusChannelMessages_Read_FiresChannelMessageEvents()
		{
			MidiReader<MidiReaderBase> midiReader;

			unsigned char buffer[] = { 0x91, 0x40, 0x70, 0x44, 0x68  };
			midiReader.InitStream(buffer, 5);

			for(int i = 0; i < 3; i++)
				Assert::IsTrue(midiReader.Read());

			Assert::IsTrue(midiReader.MidiMsg != NULL);
			Assert::AreEqual((int)Midi::NoteOn, (int)midiReader.MidiMsg->MessageType);
			Assert::AreEqual((unsigned char)1, midiReader.MidiMsg->Channel);
			Assert::AreEqual((unsigned char)0x40, midiReader.MidiMsg->Note);
			Assert::AreEqual((unsigned char)0x70, midiReader.MidiMsg->Velocity);

			for(int i = 0; i < 2; i++)
				Assert::IsTrue(midiReader.Read());

			Assert::IsTrue(midiReader.MidiMsg != NULL);
			Assert::AreEqual((int)Midi::NoteOn, (int)midiReader.MidiMsg->MessageType);
			Assert::AreEqual((unsigned char)1, midiReader.MidiMsg->Channel);
			Assert::AreEqual((unsigned char)0x44, midiReader.MidiMsg->Note);
			Assert::AreEqual((unsigned char)0x68, midiReader.MidiMsg->Velocity);
		}
	};

	
}
