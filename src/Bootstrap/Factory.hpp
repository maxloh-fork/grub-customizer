/*
 * Copyright (C) 2010-2014 Daniel Richter <danielrichter2007@web.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef SRC_BOOTSTRAP_FACTORY_HPP_
#define SRC_BOOTSTRAP_FACTORY_HPP_

#include "../View/Trait/ViewAware.hpp"

class Bootstrap_Factory
{
	public: template <typename TController, typename TView> std::shared_ptr<TController> createController(std::shared_ptr<TView> view)
	{
		auto controller = std::make_shared<TController>();

		controller->setView(view);

		return controller;
	}
};

#endif /* SRC_BOOTSTRAP_FACTORY_HPP_ */
