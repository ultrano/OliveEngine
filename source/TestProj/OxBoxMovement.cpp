
#include "NxPhysics.h"
#include "OxBoxMovement.h"
#include "OvXNode.h"
#include "OliveValue.h"


OxBoxMovement::OxBoxMovement( NxScene * scene, OvPoint3& vel ) : m_time( 0 )
, m_radian( 0 )
, m_actor( NULL )	
, m_scene( scene )
, m_vel( vel )
{

}

OxBoxMovement::~OxBoxMovement()
{
	if ( m_scene && m_actor )
	{
		m_scene->releaseActor( *m_actor );
		m_actor = NULL;
	}
}

void OxBoxMovement::Update( float _fElapse )
{
	if( NULL == m_actor ) return ;

	GetTarget()->SetTranslate( OvConvert::xyz<OvPoint3>( m_actor->getGlobalPosition() ) );
	GetTarget()->SetRotation( OvConvert::xyzw<OvQuaternion>( m_actor->getGlobalOrientationQuat() ) );

	m_time++;
	if( m_time >= 1500 )
	{
		GetTarget()->SetControlFlag(OvXObject::UPDATABLE,false);
		GetTarget()->SetControlFlag(OvXObject::VISIBLE,false);
		OvXNodeSPtr xnode = GetTarget()->GetAttachedNode();
		if ( xnode )
		{
			xnode->DettachChild( GetTarget() );
		}
	}
}

void OxBoxMovement::SetUp()
{
	if(m_scene == NULL) return;	

	// Create body
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.5f;

	OvPoint3 scale = GetTarget()->GetScale();
	NxBoxShapeDesc desc;
	desc.dimensions = OvConvert::xyz<NxVec3>( scale / 2.0f );
	//desc.materialIndex = 1;
	desc.localPose.t = NxVec3(0.0f,scale.y * 0.5f,0.0f);

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&desc);
	actorDesc.body			= &bodyDesc;
	actorDesc.density		= 1.0f;
	m_actor = m_scene->createActor( actorDesc );

	if ( m_actor )
	{
		m_actor->setGlobalPosition( OvConvert::xyz<NxVec3>( GetTarget()->GetTranslate() ) );
		m_actor->setGlobalOrientationQuat( OvConvert::xyzw<NxQuat>( GetTarget()->GetRotation() ) );
		m_actor->addForce( OvConvert::xyz<NxVec3>( m_vel * 20000 ) );

	}
	else
	{
		OvXNodeSPtr xnode = GetTarget()->GetAttachedNode();
		if ( xnode )
		{
			xnode->DettachChild( GetTarget() );
		}
	}
}

void OxBoxMovement::ShutDown()
{
	if ( m_scene && m_actor )
	{
		m_scene->releaseActor( *m_actor );
		m_actor = NULL;
	}
}