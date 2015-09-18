#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Control.h"
#include "..\ArduinoTemplateLibrary\VerticalPanel.h"
#include "TestControls.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
    [TestClass]
    public ref class VerticalPanelTest
    {
    public:
        [TestMethod]
        void VP_CurrentControl_NoCurrentCtrl_Null()
        {
            VerticalPanel<2> tested;
            TestInputControl tic;

            Assert::IsFalse(tested.getCurrentControl() != NULL);

            tested.Add(&tic);

            Assert::IsFalse(tested.getCurrentControl() != NULL);
        }

        [TestMethod]
        void VP_KeyUp_NoCurrentCtrl_SelectsLastControl()
        {
            VerticalPanel<2> tested;
            TestInputControl tic1;
            TestInputControl tic2;

            tested.Add(&tic1);
            tested.Add(&tic2);

            bool handled = tested.OnNavigationCommand(Up);

            Assert::IsTrue(handled);
            Assert::IsTrue(tested.getCurrentControl() != NULL);
            Assert::IsTrue(&tic2 == tested.getCurrentControl());
        }

        [TestMethod]
        void VP_KeyDown_NoCurrentCtrl_SelectsFirstControl()
        {
            VerticalPanel<2> tested;
            TestInputControl tic1;
            TestInputControl tic2;

            tested.Add(&tic1);
            tested.Add(&tic2);

            bool handled = tested.OnNavigationCommand(Down);

            Assert::IsTrue(handled);
            Assert::IsTrue(tested.getCurrentControl() != NULL);
            Assert::IsTrue(&tic1 == tested.getCurrentControl());
        }

        [TestMethod]
        void VP_KeyLeft_NoCurrentCtrl_NotHandled()
        {
            VerticalPanel<2> tested;
            TestInputControl tic1;
            TestInputControl tic2;

            tested.Add(&tic1);
            tested.Add(&tic2);

            bool handled = tested.OnNavigationCommand(Left);

            Assert::IsFalse(handled);
            Assert::IsFalse(tested.getCurrentControl() != NULL);
        }

        [TestMethod]
        void VP_KeyRight_NoCurrentCtrl_NotHandled()
        {
            VerticalPanel<2> tested;
            TestInputControl tic1;
            TestInputControl tic2;

            tested.Add(&tic1);
            tested.Add(&tic2);

            bool handled = tested.OnNavigationCommand(Right);

            Assert::IsFalse(handled);
            Assert::IsFalse(tested.getCurrentControl() != NULL);
        }
    };
}
