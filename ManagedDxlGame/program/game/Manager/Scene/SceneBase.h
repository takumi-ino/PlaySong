#pragma once
#include "../SceneManager.h"


// �e�V�[������
class Scenes {
public:

	// �e�L�X�g�A�I�u�W�F�N�g�`��
	virtual void  Render() {}
	// ���t���[���X�V
	virtual void  Update(float deltaTime) {}

	virtual void Destroy() {}
};