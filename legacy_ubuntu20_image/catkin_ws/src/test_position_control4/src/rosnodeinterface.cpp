//
// File rosnodeinterface.cpp
//
// Code generated for Simulink model 'test_position_control4'.
//
// Model version                  : 1.11
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Thu Jan 15 17:47:11 2026
//

#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4265)
#pragma warning(disable : 4458)
#pragma warning(disable : 4100)
#pragma comment(lib, "Ws2_32.lib")

#else

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"

#endif                                 //_MSC_VER

#include "test_position_control4.h"
#include "rosnodeinterface.h"
#include <thread>
#include <chrono>
#include <utility>

namespace ros
{
  namespace matlab
  {
    NodeInterface::NodeInterface()
      : mNode()
      , mBaseRateSem()
      , mBaseRateThread()
      , mSchedulerThread()
      , mExtModeThread()
      , mStopSem()
      , mRunModel(true)
    {
    }

    NodeInterface::~NodeInterface()
    {
      terminate();
    }

    void NodeInterface::initialize(int argc, char ** argv)
    {
      try {
        mNode = std::make_shared<ros::NodeHandle>();
        ROS_INFO("** Starting the model \"test_position_control4\" **\n");

        {
          char* extmodeArg[] = { "-port", "17725", "-blocking", "1", "-verbose",
            "0" };

          rtExtModeParseArgs(6, (const char_T **)extmodeArg, NULL);
        }

        // initialize the model which will initialize the publishers and subscribers
        rtmSetErrorStatus(test_position_control4_M, (NULL));
        test_position_control4_initialize();

        /* External mode */
        rtSetTFinalForExtMode(&rtmGetTFinal(test_position_control4_M));
        rtExtModeCheckInit(1);

        {
          boolean_T rtmStopReq = false;
          rtExtModeWaitForStartPkt(test_position_control4_M->extModeInfo, 1,
            &rtmStopReq);
          if (rtmStopReq) {
            rtmSetStopRequested(test_position_control4_M, true);
          }
        }

        rtERTExtModeStartMsg();
        mExtModeThread = std::make_shared<std::thread>(&NodeInterface::
          extmodeBackgroundTask, this);

        // create the threads for the rates in the Model
        mBaseRateThread = std::make_shared<std::thread>(&NodeInterface::
          baseRateTask, this);

        // create scheduler thread
        mSchedulerThread = std::make_shared<std::thread>(&NodeInterface::
          schedulerThread, this);
      } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        throw ex;
      }
    }

    int NodeInterface::run()
    {
      ros::spin();
      mRunModel = false;
      return 0;
    }

    boolean_T NodeInterface::getStopRequestedFlag(void)
    {

#ifndef rtmGetStopRequested

      return (!(rtmGetErrorStatus(test_position_control4_M)
                == (NULL)));

#else

      return (!(rtmGetErrorStatus(test_position_control4_M)
                == (NULL)) || rtmGetStopRequested(test_position_control4_M));

#endif

    }

    void NodeInterface::terminate(void)
    {
      if (mBaseRateThread.get()) {
        mBaseRateSem.notify();
        mBaseRateThread->join();
        mRunModel = false;
        mBaseRateThread.reset();
        if (mSchedulerThread.get()) {
          mSchedulerThread->join();
          mSchedulerThread.reset();
        }

        test_position_control4_terminate();
        rtExtModeShutdown(1);
        mNode.reset();
      }
    }

    //
    // Scheduler Task using ROS Wall clock timer to run base-rate
    //
    void NodeInterface::schedulerThread(void)
    {
      while (mRunModel) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(12500000));
        mBaseRateSem.notify();
      }
    }

    // Base-rate task
    void NodeInterface::baseRateTask(void)
    {
      mRunModel = (rtmGetErrorStatus(test_position_control4_M) ==
                   (NULL));
      while (mRunModel) {
        mBaseRateSem.wait();

#ifdef MW_DEBUG_LOG

        ROS_INFO("** Base rate task semaphore received\n");

#endif

        if (!mRunModel)
          break;

        /* External mode */
        {
          boolean_T rtmStopReq = false;
          rtExtModePauseIfNeeded(test_position_control4_M->extModeInfo, 1,
            &rtmStopReq);
          if (rtmStopReq) {
            rtmSetStopRequested(test_position_control4_M, true);
          }

          if (rtmGetStopRequested(test_position_control4_M) == true) {
            rtmSetErrorStatus(test_position_control4_M, "Simulation finished");
            mRunModel = false;
            break;
          }
        }

        test_position_control4_step();
        rtExtModeCheckEndTrigger();
        mRunModel = !NodeInterface::getStopRequestedFlag();
      }

      // Shutdown the ROS node
      ros::shutdown();
    }

    void NodeInterface::extmodeBackgroundTask(void)
    {
      while (mRunModel) {
        /* External mode */
        {
          boolean_T rtmStopReq = false;
          rtExtModeOneStep(test_position_control4_M->extModeInfo, 1,
                           &rtmStopReq);
          if (rtmStopReq) {
            rtmSetStopRequested(test_position_control4_M, true);
          }
        }
      }
    }
  }                                    //namespace matlab
}                                      //namespace ros

#ifdef _MSC_VER

#pragma warning(pop)

#else

#pragma GCC diagnostic pop

#endif                                 //_MSC_VER
