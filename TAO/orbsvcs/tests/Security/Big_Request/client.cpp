
#include "TX_ObjectC.h"

#include "ace/Get_Opt.h"

ACE_RCSID (Big_Request,
           client,
           "$Id$")

const char *ior = "file://test.ior";

int
parse_args (int argc, char *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, "k:");
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'k':
        ior = get_opts.optarg;
        break;
      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "Usage:  %s "
                           "-k <ior> "
                           "\n",
                           argv [0]),
                          -1);
      }

  // Indicates sucessful parsing of the command line
  return 0;
}

int
main (int argc, char *argv[])
{
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (::parse_args (argc, argv) != 0)
        return 1;

      CORBA::Object_var obj =
        orb->string_to_object (ior, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (obj.in ()))
        ACE_ERROR_RETURN ((LM_ERROR,
                           "ERROR: Nil server object reference\n"),
                          -1);

      TX_Object_var txObject =
        TX_Object::_narrow (obj.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      DataSeq data_input;

      CORBA::ULong len = 3461724;

      data_input.length (len);

      // Fill in some useless data.
      for (CORBA::ULong i = 0; i < len; ++i)
        data_input[i] = i % 9;

      ACE_DEBUG ((LM_DEBUG,
                  "Sending octet sequence of length %u\n",
                  data_input.length()));

      txObject->send (data_input, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      DataSeq_var data_output;

      txObject->recv (data_output.out (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      ACE_DEBUG ((LM_DEBUG,
                  "Received octet sequence of length %u\n",
                  data_output->length()));

      txObject->shutdown (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "ERROR");

      return -1;
    }
  ACE_ENDTRY;

  ACE_DEBUG ((LM_DEBUG,
              "\n"
              "SSLIOP Big_Request test passed.\n"));

  return 0;
}
