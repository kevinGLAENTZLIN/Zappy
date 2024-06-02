/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ErrorGUI.hpp
*/

#pragma once
#include <exception>
#include <iostream>

namespace Zappy {

    enum ErrorType {
        SOCKET_ERROR,
        ARG_ERROR
    };

    class ErrorGUI : public std::exception {
        public:
            ErrorGUI(const std::string &msg);
            ErrorGUI(ErrorType error);
            ErrorGUI(ErrorType error, const std::string &msg);
            virtual ~ErrorGUI() = default;

            const char* what() const noexcept override;

        private:
            mutable std::string _msg;
    };
}
