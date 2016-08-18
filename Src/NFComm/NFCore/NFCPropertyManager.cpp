// -------------------------------------------------------------------------
//    @FileName         :    NFCPropertyManager.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-03-01
//    @Module           :    NFCPropertyManager
//
// -------------------------------------------------------------------------

#include "NFCProperty.h"
#include "NFCPropertyManager.h"

NFCPropertyManager::~NFCPropertyManager()
{
    ClearAll();
}

bool NFCPropertyManager::RegisterCallback(const std::string& strProperty, const PROPERTY_EVENT_FUNCTOR_PTR& cb)
{
    NF_SHARE_PTR<NFIProperty> pProperty = this->GetElement(strProperty);
    if (pProperty.get())
    {
        pProperty->RegisterCallback(cb);
        return true;
    }

    return false;
}

NF_SHARE_PTR<NFIProperty> NFCPropertyManager::AddProperty(const NFGUID& self, NF_SHARE_PTR<NFIProperty> pProperty)
{
    const std::string& strProperty = pProperty->GetKey();
    NF_SHARE_PTR<NFIProperty> pOldProperty = this->GetElement(strProperty);
    if (!pOldProperty.get())
    {
        NF_SHARE_PTR<NFIProperty> pNewProperty(NF_NEW NFCProperty(self, strProperty, pProperty->GetType()));

        pNewProperty->SetPublic(pProperty->GetPublic());
        pNewProperty->SetPrivate(pProperty->GetPrivate());
        pNewProperty->SetSave(pProperty->GetSave());
        pNewProperty->SetCache(pProperty->GetCache());
        pNewProperty->SetRelationValue(pProperty->GetRelationValue());

        this->AddElement(strProperty, pNewProperty);
    }

    return pOldProperty;
}

NF_SHARE_PTR<NFIProperty> NFCPropertyManager::AddProperty(const NFGUID& self, const std::string& strPropertyName, const TDATA_TYPE varType)
{
    NF_SHARE_PTR<NFIProperty> pProperty = this->GetElement(strPropertyName);
    if (!pProperty.get())
    {
        pProperty = NF_SHARE_PTR<NFIProperty>(NF_NEW NFCProperty(self, strPropertyName, varType));

        this->AddElement(strPropertyName, pProperty);
    }

    return pProperty;
}

bool NFCPropertyManager::SetProperty(const std::string& strPropertyName, const NFIDataList::TData& TData)
{
    NF_SHARE_PTR<NFIProperty> pProperty = GetElement(strPropertyName);
    if (pProperty.get())
    {
        pProperty->SetValue(TData);

        return true;
    }

    return false;
}

const NFGUID& NFCPropertyManager::Self()
{
    return mSelf;
}

bool NFCPropertyManager::SetPropertyInt(const std::string& strPropertyName, const NFINT64 nValue)
{
    NF_SHARE_PTR<NFIProperty> pProperty = GetElement(strPropertyName);
    if (pProperty.get())
    {
        return pProperty->SetInt(nValue);
    }

    return false;
}

bool NFCPropertyManager::SetPropertyFloat(const std::string& strPropertyName, const double dwValue)
{
    NF_SHARE_PTR<NFIProperty> pProperty = GetElement(strPropertyName);
    if (pProperty.get())
    {
        return pProperty->SetFloat(dwValue);
    }

    return false;
}

bool NFCPropertyManager::SetPropertyString(const std::string& strPropertyName, const std::string& strValue)
{
    NF_SHARE_PTR<NFIProperty> pProperty = GetElement(strPropertyName);
    if (pProperty.get())
    {
        return pProperty->SetString(strValue);
    }

    return false;
}

bool NFCPropertyManager::SetPropertyObject(const std::string& strPropertyName, const NFGUID& obj)
{
    NF_SHARE_PTR<NFIProperty> pProperty = GetElement(strPropertyName);
    if (pProperty.get())
    {
        return pProperty->SetObject(obj);
    }

    return false;
}

NFINT64 NFCPropertyManager::GetPropertyInt(const std::string& strPropertyName)
{
    NF_SHARE_PTR<NFIProperty> pProperty = GetElement(strPropertyName);
    if (pProperty.get())
    {
        return pProperty->GetInt();
    }

    return 0;
}

double NFCPropertyManager::GetPropertyFloat(const std::string& strPropertyName)
{
    NF_SHARE_PTR<NFIProperty> pProperty = GetElement(strPropertyName);
    if (pProperty.get())
    {
        return pProperty->GetFloat();
    }

    return 0.0;
}

const std::string& NFCPropertyManager::GetPropertyString(const std::string& strPropertyName)
{
    NF_SHARE_PTR<NFIProperty> pProperty = GetElement(strPropertyName);
    if (pProperty.get())
    {
        return pProperty->GetString();
    }

    return NULL_STR;
}

const NFGUID& NFCPropertyManager::GetPropertyObject(const std::string& strPropertyName)
{
    NF_SHARE_PTR<NFIProperty> pProperty = GetElement(strPropertyName);
    if (pProperty.get())
    {
        return pProperty->GetObject();
    }

    return NULL_OBJECT;
}
