// Reviewed on: 2024-09-17
#include <iostream>
#include <type_traits>

#include "Cinema.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void clear_screen() {
	#ifdef _WIN32
		std::system("cls");
	#else
		std::system("clear");
	#endif
}

enum TYPE {
	INT_,
	FLOAT_,
};

template <typename T>
void cast_string(std::string input, T &target, TYPE type) {
	switch (type) {
		case INT_:
			if (std::is_same <T, int>::value)
				target = std::stoi(input);
			else
				throw std::invalid_argument("Error: target type does not match INT");
			break;
		case FLOAT_:
			if (std::is_same <T, float>::value)
				target = std::stof(input);
			else
				throw std::invalid_argument("Error: target type does not match FLOAT");
			break;
		default:
			throw std::invalid_argument("Error: invalid type specified");
	}
}

void read_input(std::string message, std::string &input) {
	std::cout << message;
	std::getline(std::cin, input);
	std::cout << "\n";
}

template <typename T>
void read_and_cast_input(std::string message, std::string &input, T &target, TYPE type) {
	while (true) {
		try {
			read_input(message, input);
			cast_string(input, target, type);
			break;
		} catch (const std::invalid_argument &e) {
			std::cerr << e.what() << "\nTry again \n";
		}
	}
}

/* -------------------------------------------------------------------------- */

GENRE ask_movie_genre(std::string &input) {
	int genre_index;
	do {
		read_and_cast_input("Enter the genre of the movie:\n"
				"1. ACTION.\n"
				"2. COMEDY.\n"
				"3. DRAMA.\n"
				"4. FANTASY.\n"
				"5. HORROR.\n"
				"6. ROMANCE.\n"
				"7. SCIFI\n"
				"8. SUSPENSE\n", input, genre_index, INT_);
	} while (1 > genre_index || genre_index > 8);
	return (GENRE) (genre_index - 1);
}

void add_movie(Cinema &cinema, std::string &input) {
	std::string name;
	GENRE genre;

	read_input("Enter the name of the movie: ", name);
	genre = ask_movie_genre(input);

	cinema.add_movie(Movie(name, genre));
	std::cout << "Movie added successfully \n";
}

void add_projection_room(Cinema &cinema, std::string &input) {
	std::string name;
	read_input("Enter the name of the projection room: ", name);
	ProjectionRoom projection_room = ProjectionRoom(name);
	for (int i = 0; i < 4;) {
		try {
			Movie movie;
			int start_hour, start_minute, end_hour, end_minute, movie_index;

			std::cout << "The available movies to project\n";
			std::cout << cinema.list_movies() + "\n";
			read_and_cast_input("Enter the index of the movie: ", input, movie_index, INT_);

			read_and_cast_input("Enter the start hour of the projection " + std::to_string(i + 1) + ": "
						, input, start_hour, INT_);

			read_and_cast_input("Enter the start minute of the projection " + std::to_string(i + 1) + ": "
						, input, start_minute, INT_);

			read_and_cast_input("Enter the end hour of the projection " + std::to_string(i + 1) + ": "
						, input, end_hour, INT_);

			read_and_cast_input("Enter the end minute of the projection " + std::to_string(i + 1) + ": "
						, input, end_minute, INT_);

			while (true) {
				try {
					movie = cinema.get_movie(movie_index - 1);
					break;
				} catch (const std::out_of_range &e) {
					std::cout << e.what() << "\n";
				}
			}
			Projection projection = Projection(movie, start_hour, start_minute
												, end_hour, end_minute);
			projection_room.add_projection(projection);
			i++;
		} catch (const std::invalid_argument &e) {
			std::cout << e.what() << "\n";
		} catch (const std::runtime_error &e) {
			std::cout << e.what() << "\n";
		}
	}
	try {
		cinema.add_projection_room(projection_room);
	} catch (std::runtime_error &e) {
		std::cout << e.what() << "\n";
	}
}

void search_movies_by_genre(Cinema &cinema, std::string &input) {
	GENRE genre = ask_movie_genre(input);

	std::cout << cinema.search_movies_by_genre(genre) << "\n";
}

void consult_movie_projection(Cinema &cinema, std::string &input) {
	int movie_index;
	read_and_cast_input("Enter the movie index: ", input, movie_index, INT_);
	std::cout << cinema.consult_movie_projections(movie_index) << "\n";
}

void generate_dummy_data(Cinema &cinema) {
	Movie movie_1 = Movie("Spider-Man: Far From Home", ACTION);
	Movie movie_2 = Movie("Toy Story 4", COMEDY);
	Movie movie_3 = Movie("The Irishman", DRAMA);
	Movie movie_4 = Movie("Avengers: Infinity War", FANTASY);
	Movie movie_5 = Movie("Us", HORROR);
	Movie movie_6 = Movie("La La Land", ROMANCE);
	Movie movie_7 = Movie("Interstellar", SCIFI);
	Movie movie_8 = Movie("Gone Girl", SUSPENSE);

	cinema.add_movie(movie_1);
	cinema.add_movie(movie_2);
	cinema.add_movie(movie_3);
	cinema.add_movie(movie_4);
	cinema.add_movie(movie_5);
	cinema.add_movie(movie_6);
	cinema.add_movie(movie_7);
	cinema.add_movie(movie_8);

	ProjectionRoom room1("Room 1");
	ProjectionRoom room2("Room 2");
	ProjectionRoom room3("Room 3");

	Projection projection1(cinema.get_movie(0), 10, 0, 12, 0);
	Projection projection2(cinema.get_movie(1), 14, 0, 16, 0);
	Projection projection3(cinema.get_movie(2), 18, 0, 21, 0);
	Projection projection4(cinema.get_movie(3), 10, 0, 13, 0);
	Projection projection5(cinema.get_movie(4), 15, 0, 17, 0);
	Projection projection6(cinema.get_movie(5), 19, 0, 21, 0);
	Projection projection7(cinema.get_movie(6), 12, 0, 15, 0);
	Projection projection8(cinema.get_movie(7), 16, 0, 18, 0);

	room1.add_projection(projection1);
	room1.add_projection(projection2);
	room2.add_projection(projection3);
	room2.add_projection(projection4);
	room3.add_projection(projection5);
	room3.add_projection(projection6);
	room3.add_projection(projection7);
	room3.add_projection(projection8);

	cinema.add_projection_room(room1);
	cinema.add_projection_room(room2);
	cinema.add_projection_room(room3);
}

int main() {
	Cinema cinema;
	int option;
	float basic_price_ticket;
	std::string input, menu;

	read_and_cast_input("Enter the basic ticket price: ", input, basic_price_ticket, FLOAT_);
	cinema.set_basic_price_ticket(basic_price_ticket);

	menu = "Welcome to the cinema\n"
		"We have the following options\n"
		"1. Add a movie.\n"
		"2. Add a projection room. \n"
		"3. Search movies by genre.\n"
		"4. Consult movie programming.\n"
		"5. List movies.\n"
		"6. Exit\n"
		"-> ";

	generate_dummy_data(cinema);

	do {
		do {
			read_and_cast_input(menu, input, option, INT_);
		} while (0 >= option || option < 5);
		clear_screen();
		switch (option) {
			case 1:
				add_movie(cinema, input);
				break;
			case 2:
				add_projection_room(cinema, input);
				break;
			case 3:
				search_movies_by_genre(cinema, input);
				break;
			case 4:
				consult_movie_projection(cinema, input);
				break;
			case 5:
				std::cout << cinema.list_movies() << "\n";
				break;
		}
	} while (input != "6");

	return 0;
}
