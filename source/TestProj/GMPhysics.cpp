#include "GMPhysics.h"
#include "OliveValue.h"
#include "OvXObject.h"

OvRTTI_IMPL( GMPhysics );


void GMPhysics::SetUp()
{
	if ( OvXObjectSPtr target = GetTarget() )
	{
		OliveValue::Point3* accelaration = target->FindExtraProperty<OliveValue::Point3>( "accelaration" );
		if ( NULL == accelaration )
		{
			accelaration = OliveValue::Factory<OliveValue::Point3>();
			accelaration->SetPoint3( OvPoint3( 0.0f, 0.097f, 0.0f) );
			target->RegisterExtraProperty( "accelaration", accelaration );
		}

		OliveValue::Point3* velocity = target->FindExtraProperty<OliveValue::Point3>( "velocity" );
		if ( NULL == velocity )
		{
			velocity = OliveValue::Factory<OliveValue::Point3>();
			velocity->SetPoint3( OvPoint3( 0.0f, 0.0f, 1.0f) );
			target->RegisterExtraProperty( "velocity", velocity );
		}

		OliveValue::Float* resistance = target->FindExtraProperty<OliveValue::Float>( "resistance" );
		if ( NULL == resistance )
		{
			resistance = OliveValue::Factory<OliveValue::Float>();
			resistance->SetFloat( 0.01f );
			target->RegisterExtraProperty( "resistance", resistance );
		}
	}
}

void GMPhysics::ShutDown()
{

}

void GMPhysics::Update( float _fElapse )
{
	_gravity( _fElapse );
	_repulsion( _fElapse );
	_friction( _fElapse );
}

void GMPhysics::_gravity( float _fElapse )
{
	OvXObjectSPtr target = GetTarget();
	if ( target )
	{
		OliveValue::Point3* accelaration = target->FindExtraProperty<OliveValue::Point3>( "accelaration" );
		OliveValue::Point3* velocity = target->FindExtraProperty<OliveValue::Point3>( "velocity" );
		if ( velocity && accelaration )
		{
			OvPoint3 pos = target->GetTranslate();
			pos -= velocity->GetPoint3();
			target->SetTranslate( pos );

			velocity->SetPoint3( velocity->GetPoint3() + accelaration->GetPoint3() );
		}
	}
}

void GMPhysics::_repulsion( float _fElapse )
{
	OvXObjectSPtr target = GetTarget();
	if ( target )
	{
		OvPoint3 pos = target->GetTranslate();
		if ( pos.y < 0.0f )
		{
			OliveValue::Point3* accelaration = target->FindExtraProperty<OliveValue::Point3>( "accelaration" );
			OliveValue::Point3* velocity = target->FindExtraProperty<OliveValue::Point3>( "velocity" );
			if ( accelaration && velocity )
			{
				OvPoint3 norm(0.0f,-1.0f,0.0f);
				const OvPoint3& vel = velocity->GetPoint3();
				OvPoint3 refnorm = _refection( vel, norm );

				//pos = refnorm * pos.Length();
				target->SetTranslate( pos );
				velocity->SetPoint3( OvPoint3( vel.x * refnorm.x, vel.y * refnorm.y, vel.z * refnorm.z) );
			}
		}
	}
}

void GMPhysics::_friction( float _fElapse )
{
	OvXObjectSPtr target = GetTarget();
	if ( target )
	{
		OliveValue::Float* resistance = target->FindExtraProperty<OliveValue::Float>( "resistance" );
		OliveValue::Point3* velocity = target->FindExtraProperty<OliveValue::Point3>( "velocity" );
		if ( resistance && velocity )
		{
			OvPoint3 friction_vel = velocity->GetPoint3();
			friction_vel = friction_vel.Normalize() * resistance->GetFloat();
			velocity->SetPoint3( velocity->GetPoint3() - friction_vel );
		}
	}
}

OvPoint3 GMPhysics::_refection( OvPoint3 inject, OvPoint3 norm )
{
	inject = inject.Normalize();
	norm = norm.Normalize();
	return ( norm  * norm.DotProduct( -inject ) * 2.0f + inject ).Normalize();
}