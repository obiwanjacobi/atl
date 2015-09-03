#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Range.h"
#include "..\ArduinoTemplateLibrary\Time.h"
#include "..\ArduinoTemplateLibrary\PID.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;
using namespace ATL::Process;

namespace ArduinoTemplateLibraryTests
{
	template<typename T>
	class PidBase : public Range<T>, public TimeEx<Milliseconds>
	{
	public:
		PidBase()
		{
			Begin = 0;
			End = 255;
		}

		T getFeedback()
		{
			return 100;
		}

		T getLargestAcceptableError()
		{
			return 0.5;
		}

		T LowPassFilter(T value, unsigned int deltaTime)
		{
			return value;
		}
	};

	[TestClass]
	public ref class PIDTest
	{
		typedef PID<PidBase<float>, float> RealPid;

	public: 
		//[TestMethod]
		void TestTemplateHiearchy()
		{
			// just a compiler test

			RealPid pid;

			pid.Process(200, 1.0, 1.0, 1.0);
		}
	};
}
