#include "Player.h"

Player::Player(Camera* pCamera)
    : camera(pCamera)
{

}

void Player::SetCameraFocus(bool focus, GLFWwindow* window)
{
    if (focus)
    {
        camera->CaptureMouse(window);
    }
    else
    {
        camera->ReleaseMouse(window);
    }
}