#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\MidiMessage.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL::Midi;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class MidiMessageTest
	{
		static const unsigned char channel = 15;
		static const unsigned char note = 64;
		static const unsigned char velocity = 100;
		static const int bend = 1024;
	public: 
		[TestMethod]
		void TestStructureDefinition_PitchBend()
		{
			MidiMessage msg;
			msg.MessageType = Midi::PitchBend;
			msg.Channel = MidiMessageTest::channel;
			msg.Bend = MidiMessageTest::bend;

			Assert::AreEqual((int)Midi::PitchBend, (int)msg.MessageType);
			Assert::AreEqual(MidiMessageTest::channel, msg.Channel);
			Assert::AreEqual(MidiMessageTest::bend, msg.Bend);
		}

		[TestMethod]
		void TestStructureDefinition_ChannelMessage()
		{
			MidiMessage msg;
			msg.MessageType = Midi::NoteOn;
			msg.Channel = MidiMessageTest::channel;
			msg.Note = MidiMessageTest::note;
			msg.Velocity = MidiMessageTest::velocity;

			Assert::AreEqual((int)Midi::NoteOn, (int)msg.MessageType);
			Assert::AreEqual(MidiMessageTest::channel, msg.Channel);
			Assert::AreEqual(MidiMessageTest::note, msg.Note);
			Assert::AreEqual(MidiMessageTest::velocity, msg.Velocity);
		}

		[TestMethod]
		void TestStructureDefinition_SongPosition()
		{
			MidiMessage msg;
			msg.MessageType = Midi::SongPosition;
			msg.Beats = 32000;

			Assert::AreEqual((int)Midi::SongPosition, (int)msg.MessageType);
			Assert::AreEqual((unsigned int)32000, msg.Beats);
		}

		[TestMethod]
		void TestSequentialInit_ChannelMessage()
		{
			MidiMessage msg;
			msg.SetStatusByte(Midi::NoteOff | MidiMessageTest::channel);
			msg.SetDataByte1(MidiMessageTest::note);
			msg.SetDataByte2(MidiMessageTest::velocity);

			Assert::AreEqual((int)Midi::NoteOff, (int)msg.MessageType);
			Assert::AreEqual(MidiMessageTest::channel, msg.Channel);
			Assert::AreEqual(MidiMessageTest::note, msg.Note);
			Assert::AreEqual(MidiMessageTest::velocity, msg.Velocity);
		}

		[TestMethod]
		void TestSequentialInit_PitchBend()
		{
			MidiMessage msg;
			msg.SetStatusByte(Midi::PitchBend | MidiMessageTest::channel);
			// bend = 1024 = 1000|0000000 = 8|0
			msg.SetDataByte1(0);
			msg.SetDataByte2(8);

			Assert::AreEqual((int)Midi::PitchBend, (int)msg.MessageType);
			Assert::AreEqual(MidiMessageTest::channel, msg.Channel);
			Assert::AreEqual(MidiMessageTest::bend, msg.Bend);
		}

		[TestMethod]
		void TestSequentialExtraction_ChannelMessage()
		{
			MidiMessage msg;
			msg.MessageType = Midi::NoteOn;
			msg.Channel = MidiMessageTest::channel;
			msg.Note = MidiMessageTest::note;
			msg.Velocity = MidiMessageTest::velocity;

			Assert::AreEqual((int)(Midi::NoteOn | MidiMessageTest::channel), (int)msg.GetStatusByte());
			Assert::AreEqual(MidiMessageTest::note, msg.GetDataByte1());
			Assert::AreEqual(MidiMessageTest::velocity, msg.GetDataByte2());
		}

		[TestMethod]
		void TestSequentialExtraction_PitchBend()
		{
			MidiMessage msg;
			msg.MessageType = Midi::PitchBend;
			msg.Channel = MidiMessageTest::channel;
			msg.Bend = MidiMessageTest::bend;

			Assert::AreEqual((int)(Midi::PitchBend | MidiMessageTest::channel), (int)msg.GetStatusByte());
			// bend = 1024 = 1000|0000000 = 8|0
			Assert::AreEqual(0, (int)msg.GetDataByte1());
			Assert::AreEqual(8, (int)msg.GetDataByte2());
		}

		[TestMethod]
		void TestCopyTo()
		{
			MidiMessage msg;
			msg.MessageType = Midi::PitchBend;
			msg.Channel = MidiMessageTest::channel;
			msg.Bend = MidiMessageTest::bend;

			MidiMessage target;
			msg.CopyTo(&target);

			Assert::AreEqual((int)msg.MessageType, (int)target.MessageType);
			Assert::AreEqual(msg.Channel, target.Channel);
			Assert::AreEqual(msg.Note, target.Note);
			Assert::AreEqual(msg.Velocity, target.Velocity);
			Assert::AreEqual(msg.Bend, target.Bend);
			Assert::AreEqual(msg.Beats, target.Beats);
		}
	};
}
