#pragma once
#include "UIDialog.h"
#include "Material.h"

class CDlgMaterial :public CUIDialog
{
public:
	CDlgMaterial();
	virtual void OnControlRegister();
	void setMaterial(const std::string& strMaterial, const std::string& strPath);
private:
	std::string getEditBoxFilename(const CUIEditBox& editBox);
	unsigned int getTextureID(const CUIEditBox& editBox);
	// Controls' event.
	void OnEditboxDiffuse();
	void OnEditboxEmissive();
	void OnEditboxSpecular();
	void OnEditboxBump();
	void OnEditboxReflection();
	void OnEditboxLightmap();
	void OnEditboxEffect();
	void OnCheckboxAlphatest();
	void OnNumAlphatestvalue();
	void OnCheckboxBlend();
	void OnCheckboxCull();
	void OnNumTexanimX();
	void OnNumTexanimY();
	void OnNumOpacity();
	void OnColorEmissive();
	void OnNumUvscaleX();
	void OnNumUvscaleY();
	void OnBtnClose();
	// Controls' variable.
	CUIEditBox	m_EditboxDiffuse;
	CUIEditBox	m_EditboxEmissive;
	CUIEditBox	m_EditboxSpecular;
	CUIEditBox	m_EditboxBump;
	CUIEditBox	m_EditboxReflection;
	CUIEditBox	m_EditboxLightmap;
	CUIEditBox	m_EditboxEffect;
	CUICheckBox	m_CheckboxAlphatest;
	CUIComboNumber	m_NumAlphatestvalue;
	CUICheckBox	m_CheckboxBlend;
	CUICheckBox	m_CheckboxCull;
	CUIComboNumber	m_NumTexanimX;
	CUIComboNumber	m_NumTexanimY;
	CUIComboNumber	m_NumOpacity;
	CUIComboColor	m_ColorEmissive;
	CUIComboNumber	m_NumUvscaleX;
	CUIComboNumber	m_NumUvscaleY;

	CMaterial* m_pSelectedMaterial;

	std::string m_strPath;
};