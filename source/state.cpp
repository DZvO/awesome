/*
 * =====================================================================================
 *
 *       Filename:  game.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/11/2010 02:28:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Der Zauberer von Oz (oz), starstrider.industries@gmail.com
 *        Company:  *none*
 *
 * =====================================================================================
 */
#include "state.hpp"

motor::State::State()
{
}

int motor::State::main(Window *wnd, Input* inp)
{
	width = wnd->width;
	height = wnd->height;
	return 0;
}

void motor::State::draw()
{

}

void motor::State::init()
{
}

void motor::State::load()
{

}

void motor::State::unload()
{

}

void motor::State::update()
{

}

