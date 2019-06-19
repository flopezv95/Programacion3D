#include "Camera.h"
#include "State.h"
#include "../glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective

Camera::Camera()
{
	mProjection = glm::mat4(1);
	mClearColor = glm::vec3(1);
	mViewPort = glm::ivec4(1);
}

const glm::mat4 & Camera::getProjection() const
{
	return mProjection;
}

void Camera::setProjection(const glm::mat4 & proj)
{
	mProjection = proj;
}

const glm::ivec4 & Camera::getViewport() const
{
	return mViewPort;
}

void Camera::setViewport(const glm::ivec4 & vp)
{
	mViewPort = vp;
}

const glm::vec3 & Camera::getClearColor() const
{
	return mClearColor;
}

void Camera::setClearColor(const glm::vec3 & color)
{
	mClearColor = color;
}

void Camera::prepare()
{
	State::projectionMatrix = mProjection;
	State::viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glViewport(mViewPort.x, mViewPort.y, mViewPort.z, mViewPort.w);
	glScissor(mViewPort.x, mViewPort.y, mViewPort.z, mViewPort.w);
	glClearColor(mClearColor.x, mClearColor.y, mClearColor.z,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
