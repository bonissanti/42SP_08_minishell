/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_recursive_descendent_math.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:31:57 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/24 18:48:10 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

int parseExpression();
int parseTerm();
int parseFactor();

int parseExpression() {
    int value = parseTerm();
    char operator;

    while (scanf(" %c", &operator) == 1 && (operator == '+' || operator == '-')) {
        scanf("%*c"); // Consume the newline character

        if (operator == '+')
            value += 
            parseTerm();
        else if (operator == '-')
            value -= parseTerm();
    }

    ungetc(operator, stdin); // Put the non-operator character back into the input buffer
    return value;
}

int parseTerm() {
    int value = parseFactor();
    char operator;

    while (scanf(" %c", &operator) == 1 && (operator == '*' || operator == '/')) {
        scanf("%*c"); // Consume the newline character

        if (operator == '*')
            value *= parseFactor();
        else if (operator == '/')
            value /= parseFactor();
    }

    ungetc(operator, stdin); // Put the non-operator character back into the input buffer
    return value;
}

int parseFactor() {
    int value;
    char operator;

    while (scanf(" %c", &operator) == 1) {
        if (operator == '(') {
            value = parseExpression();
            scanf("%*c"); // Consume the newline character
            scanf(" %c", &operator); // Discard the closing parenthesis
        } else if (operator >= '0' && operator <= '9') {
            ungetc(operator, stdin); // Put the digit back into the input buffer
            scanf("%d", &value);
            scanf("%*c"); // Consume the newline character
            return value;
        } else {
            exit(EXIT_FAILURE); // Invalid input
        }
    }

    exit(EXIT_FAILURE); // Invalid input
}

int main() {
    int result = parseExpression();

    printf("Result: %d\n", result);

    return 0;
}
