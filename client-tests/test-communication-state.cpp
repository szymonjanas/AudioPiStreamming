#include "catch.hpp"
#include <zmq.hpp>
#include "media/communication-state.hpp"

SCENARIO("Testing communication state","[state converter]")
{

    GIVEN ("Converter")
    {
        Communication_state_converter converter;
        WHEN("give string to convert and enum expected")
        {
            THEN("convert to server request")
            {
                Replay expected_state = Replay::SERVER_CONNECTED;
                std::string message = "SERV-TESTC-CONND";
                Replay replay = converter.convert_server_msg_to_replay(message);
                REQUIRE(expected_state == replay);
            }
        }

        WHEN("give string request to convert and enum expected")
        {
            THEN("convert to request")
            {
                std::string req_msg = "SERV-TESTC-CONN";
                Request expected = Request::SERVER_TEST_CONNECTION;
                Request req = converter.convert_client_request_msg(req_msg);
                REQUIRE(req == expected);
            }
        }
    }
}
