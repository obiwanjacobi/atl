# Midi

The Midi implementation in ATL consists of reading and writing `MidiMessage`s to and from a `Stream`.

The `MidiMessage` structure contains all information for all types of Midi  messages - currently System Exclusive messages are not yet implemented. When reading Midi the information will be presented in `MidiMessage` instances and when writing the program must deliver the Midi information to sent as a `MidiMessage` instance.

The `MidiMessage` structure contains a somewhat complex union structure that declares appropriate member variables for all types of Midi messages - without taking more memory than strictly needed.

## Streams

Before diving into Midi further it is important to note that ATL uses an abstraction for `InputStream`s and `OutputStream`s. The Midi implementation uses these abstractions. ATL comes with adapter classes to wrap an Arduino `Serial` stream as one of the ATL abstractions.

## Writing Midi

The `MidiWriter` class implements the Midi protocol logic for writing a `MidiMessage` to a stream. Its BaseT is assumed to be an `OutputStream` that implements the `Write(byte)` method. Any class that has that method declaration can be used as a BaseT.

To write a `MidiMessage` to the underlying `OutputStream` simply call the `Write(MidiMessage*)` method. The writer class keeps track of running status to optimize the number of bytes actually sent to the `OutputStream`.

## Reading Midi

The `MidiReader` class is a little more complex for it has to deliver the `MidiMessage`s to the program - without using virtual methods. The `MidiReader` class implements the protocol for reading Midi messages from an `InputStream`.

The `bool Read()` method is meant to be called repeatedly in the program and pumps the bytes from the `InputStream` through the `MidiReader` class to the program. It is the only public method.

The BaseT of the `MidiReader` class is provided by the program and implements a couple of methods to receive the `MidiMessage`s as they come in - currently System Exclusive messages are not implemented yet. The BaseT is also used to access the `InputStream`, so the program-supplied base class could also use the same 'BaseT-principle' to inherit from the required `InputStream`.

It is important to note that the `MidiMessage*` parameter that is provided in the 'callback' method to the program is only valid during that call. This means that the program must copy the information if it needs to store it. A `MidiMessage::CopyTo` is available for that purpose.

There are also 'callback' methods for real-time Midi messages (1 byte) and System Exclusive messages (not implemented).
