#pragma once
#include <Physics2012/Vehicle/hkpVehicleInstance.h>

#include <Physics2012/Vehicle/AeroDynamics/Default/hkpVehicleDefaultAerodynamics.h>
#include <Physics2012/Vehicle/DriverInput/Default/hkpVehicleDefaultAnalogDriverInput.h>
#include <Physics2012/Vehicle/Brake/Default/hkpVehicleDefaultBrake.h>
#include <Physics2012/Vehicle/Engine/Default/hkpVehicleDefaultEngine.h>
#include <Physics2012/Vehicle/VelocityDamper/Default/hkpVehicleDefaultVelocityDamper.h>
#include <Physics2012/Vehicle/Steering/Default/hkpVehicleDefaultSteering.h>
#include <Physics2012/Vehicle/Suspension/Default/hkpVehicleDefaultSuspension.h>
#include <Physics2012/Vehicle/Transmission/Default/hkpVehicleDefaultTransmission.h>
#include <Physics2012/Vehicle/WheelCollide/RayCast/hkpVehicleRayCastWheelCollide.h>
#include <Physics2012/Vehicle/TyreMarks/hkpTyremarksInfo.h>

class VehicleSetup
{
public:
	  VehicleSetup() :
    m_up(hkVector4(0, 0, 1)),
    m_forward(hkVector4(1, 0, 0)),
    m_right(hkVector4(0, -1, 0))
    {}
	  
	VehicleSetup(hkVector4& up, hkVector4& forward, hkVector4& right) :
    m_up(up),
    m_forward(forward),
    m_right(right)
    {}

	virtual ~VehicleSetup(void){};

	 void buildVehicle( const hkpWorld* world, hkpVehicleInstance& vehicle ); 

  void setupVehicleData( const hkpWorld* world, hkpVehicleData& data );
  void setupComponent( const hkpVehicleData& data, hkpVehicleDefaultSuspension& suspension );
  void setupComponent( const hkpVehicleData& data, hkpVehicleDefaultSteering& steering );
  void setupComponent( const hkpVehicleData& data, hkpVehicleDefaultAnalogDriverInput& driverInput );
  void setupComponent( const hkpVehicleData& data, hkpVehicleDefaultEngine& engine );
  void setupComponent( const hkpVehicleData& data, hkpVehicleDefaultTransmission& transmission );
  void setupComponent( const hkpVehicleData& data, hkpVehicleDefaultBrake& brake );
  void setupComponent( const hkpVehicleData& data, hkpVehicleDefaultAerodynamics& aerodynamics );
  void setupComponent( const hkpVehicleData& data, hkpVehicleDefaultVelocityDamper& velocityDamper );
  void setupWheelCollide( const hkpWorld* world, const hkpVehicleInstance& vehicle, hkpVehicleRayCastWheelCollide& wheelCollide );
  void setupTyremarks( const hkpVehicleData& data, hkpTyremarksInfo& tyremarkscontroller );


	private:
  hkReal m_wheelRadius;
  hkVector4 m_up;
  hkVector4 m_forward;
  hkVector4 m_right;
};

