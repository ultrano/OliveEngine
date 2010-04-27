

template<typename Class_0>
OvObjectSPtr	OvObjectFactory::TemplateManufactureFunctor(OvStorage& cConstructDesc)
{
	return OvNew Class_0(cConstructDesc);
};

template<typename Class_0>
void			OvObjectFactory::RegisterClassManufacture(const char* pClassName)
{
	GetInstance()->m_mapManufactures[pClassName] = TemplateManufactureFunctor<Class_0>;
};