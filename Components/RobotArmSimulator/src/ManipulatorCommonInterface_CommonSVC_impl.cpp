// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_CommonSVC_impl.cpp
 * @brief Service implementation code of ManipulatorCommonInterface_Common.idl
 *
 */

#include "ManipulatorCommonInterface_CommonSVC_impl.h"


/*
 * Example implementational code for IDL interface JARA_ARM::ManipulatorCommonInterface_Common
 */
ManipulatorCommonInterface_CommonSVC_impl::ManipulatorCommonInterface_CommonSVC_impl(RobotArm *ra)
{
  // Please add extra constructor code here.
  m_robotArm = ra;
}


ManipulatorCommonInterface_CommonSVC_impl::~ManipulatorCommonInterface_CommonSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::clearAlarms()
{
	JARA_ARM::RETURN_ID_var result = new JARA_ARM::RETURN_ID();
  return result._retn();
}

JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getActiveAlarm(JARA_ARM::AlarmSeq_out alarms)
{
	alarms = new JARA_ARM::AlarmSeq;
	JARA_ARM::RETURN_ID_var result = new JARA_ARM::RETURN_ID();
  return result._retn();
}

JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getFeedbackPosJoint(JARA_ARM::JointPos_out pos)
{
	pos = new JARA_ARM::JointPos;
	pos->length(m_robotArm->axisNum);
	for(int i=0;i < m_robotArm->axisNum;i++)
	{
		(*pos)[i] = m_robotArm->theta[i];
	}

	JARA_ARM::RETURN_ID_var result = new JARA_ARM::RETURN_ID();
  return result._retn();
}

JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getManipInfo(JARA_ARM::ManipInfo_out mInfo)
{
	mInfo = new JARA_ARM::ManipInfo;
	mInfo->manufactur = m_robotArm->manifactur.c_str();
	mInfo->type = m_robotArm->type.c_str();
	mInfo->axisNum = m_robotArm->axisNum;
	mInfo->cmdCycle = m_robotArm->cmdCycle;
	mInfo->isGripper = m_robotArm->isGripper;

	JARA_ARM::RETURN_ID_var result = new JARA_ARM::RETURN_ID();
  return result._retn();
}

JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getSoftLimitJoint(JARA_ARM::LimitSeq_out softLimit)
{
	softLimit = new JARA_ARM::LimitSeq;
	softLimit->length(m_robotArm->axisNum);
	for(int i=0;i < m_robotArm->axisNum;i++)
	{
		(*softLimit)[i].lower = m_robotArm->softUpperLimitJoint[i];
		(*softLimit)[i].upper = m_robotArm->softLowerLimitJoint[i];
	}

	JARA_ARM::RETURN_ID_var result = new JARA_ARM::RETURN_ID();
  return result._retn();
}

JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getState(JARA_ARM::ULONG& state)
{
	state = 0;
	JARA_ARM::RETURN_ID_var result = new JARA_ARM::RETURN_ID();
  return result._retn();
}

JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::servoOFF()
{
	m_robotArm->setSerbo(false);
	JARA_ARM::RETURN_ID_var result = new JARA_ARM::RETURN_ID();
  return result._retn();
}

JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::servoON()
{
	m_robotArm->setSerbo(true);
	JARA_ARM::RETURN_ID_var result = new JARA_ARM::RETURN_ID();
  return result._retn();
}

JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::setSoftLimitJoint(const JARA_ARM::LimitSeq &softLimit)
{
	for(int i=0;i<softLimit.length()&&i<m_robotArm->axisNum;i++){
		m_robotArm->softUpperLimitJoint[i] = softLimit[i].lower;
		m_robotArm->softLowerLimitJoint[i] = softLimit[i].upper;
	}
	JARA_ARM::RETURN_ID_var result = new JARA_ARM::RETURN_ID();
  return result._retn();
}



// End of example implementational code



