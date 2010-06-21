#include "UIComboObjListSceneObject.h"
#include "Scene.h"

CUIComboObjListSceneObject::CUIComboObjListSceneObject()
{
}

CUIComboObjListSceneObject::~CUIComboObjListSceneObject()
{	
}

void CUIComboObjListSceneObject::OnListBoxObjectSelection()
{
	if (NULL==m_pScene)
	{
		return;
	}
	CScene::MAP_OBJECT_INFO& sceneObjectInfo = m_pScene->GetObjectInfo();
	if (sceneObjectInfo.find(getSelectedObjectID())!=sceneObjectInfo.end())
	{
		const CScene::ObjectInfo& objectInfo = sceneObjectInfo[getSelectedObjectID()];
		m_ModelObject.load(objectInfo.strFilename);
	}
}

void CUIComboObjListSceneObject::initObject(CScene& scene)
{
	m_pScene=&scene;
	m_ListBoxObject.RemoveAllItems();
	CScene::MAP_OBJECT_INFO& sceneObjectInfo = scene.GetObjectInfo();
	for (CScene::MAP_OBJECT_INFO::iterator it = sceneObjectInfo.begin();
		it!=sceneObjectInfo.end(); it++)
	{
		m_ListBoxObject.AddItem(s2ws(it->second.strName).c_str(),(LPVOID)it->first);
	}
}

void CUIComboObjListSceneObject::SelectObjectByObjectID(int64 id)
{
	if (NULL==m_pScene)
	{
		return;
	}
	{
		CScene::MAP_OBJECT_INFO& sceneObjectInfo = m_pScene->GetObjectInfo();
		if (sceneObjectInfo.find(id)!=sceneObjectInfo.end())
		{
			const CScene::ObjectInfo& objectInfo = sceneObjectInfo[id];
			m_ModelObject.load(objectInfo.strFilename);
		}
	}
	int nIndex = m_ListBoxObject.getItemIndexByData((void*)(id));
	m_ListBoxObject.SelectItem(nIndex);
}

size_t CUIComboObjListSceneObject::getSelectedObjectID()
{
	return (size_t)m_ListBoxObject.GetSelectedData();
}

void CUIComboObjListSceneObject::OnObjectListReload()
{
	//std::string strObjectListFilename = getDisplay().getScene().getObjectListFilename();
	//getDisplay().getScene().loadObjectList(strObjectListFilename,strObjectListFilename);
	//initObject();
	//std::string strTileListFilename = getDisplay().getTerrain().getTileListFilename();
	////getDisplay().getTerrain().LoadTiles(strTileListFilename);
	//initTiles();
}

void CUIComboObjListSceneObject::OnObjectListEdit()
{
	//std::string strObjectListFilename = getDisplay().getScene().getObjectListFilename();
	//ShellExecuteW(NULL,L"open",s2ws(strObjectListFilename).c_str(),NULL,NULL,SW_SHOWNORMAL); 
	//std::string strTileListFilename = getDisplay().getTerrain().getTileListFilename();
	//ShellExecuteW(NULL,L"open",s2ws(strTileListFilename).c_str(),NULL,NULL,SW_SHOWNORMAL); 
}

void CUIComboObjListSceneObject::OnFrameMove(double fTime, float fElapsedTime)
{
	CUIComboObjList::OnFrameMove(fTime, fElapsedTime);
	m_ModelObject.OnFrameMove(fElapsedTime);
	m_ModelObject.updateEmitters(Matrix::UNIT,fElapsedTime);
}

void CUIComboObjListSceneObject::OnFrameRender(const Matrix& mTransform, double fTime, float fElapsedTime)
{
	CUIComboObjList::OnFrameRender(mTransform,fTime, fElapsedTime);
	CRenderSystem& R = GetRenderSystem();
	R.setViewport(m_ListBoxDisplay.GetBoundingBox());
	R.SetSamplerFilter(0, TEXF_LINEAR, TEXF_LINEAR, TEXF_LINEAR);
	R.SetSamplerFilter(1, TEXF_LINEAR, TEXF_LINEAR, TEXF_LINEAR);
	Matrix mView,mProj;
	BBox bbox;
	if (m_ModelObject.getModelData())
	{
		bbox = m_ModelObject.getModelData()->m_Mesh.m_bbox;
	}
	Vec3D vCenter = (bbox.vMax+bbox.vMin)*0.5f;
	float fWidth = (bbox.vMax-bbox.vMin).length();
	float fHeight = fWidth*(m_ListBoxDisplay.GetBoundingBox().bottom-m_ListBoxDisplay.GetBoundingBox().top)/
		(m_ListBoxDisplay.GetBoundingBox().right-m_ListBoxDisplay.GetBoundingBox().left);
	mView.MatrixLookAtLH(Vec3D(sinf(fTime)*fWidth,abs(sinf(fTime*0.1f)*fWidth),cosf(fTime)*fWidth),vCenter,Vec3D(0,1.0f,0));
	mProj.MatrixOrthoLH(fWidth,fHeight,0.1f, 256.0f);
	R.setViewMatrix(mView);
	R.setProjectionMatrix(mProj);
	R.setWorldMatrix(Matrix::UNIT);
	{
		R.ClearBuffer(true,false,0x0);
		m_ModelObject.render();
	}
	R.SetupRenderState();
	R.setViewport(GetParentDialog()->GetParentDialog()->GetParentDialog()->GetBoundingBox());
}