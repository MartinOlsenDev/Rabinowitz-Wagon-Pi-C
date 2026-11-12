#include <stdio.h>
#include <stdlib.h>

div_t make_c_entry (size_t current_idx);

long long make_pi_digits (size_t count);
void print_pi_digits(size_t count);

int
main ([[maybe_unused]] int argc, char *argv[static 2])
{
  size_t const pi_digit_requested = strtoull (argv[1], nullptr, 10);
  // long long my_pi = make_pi_digits (pi_digit_requested+1);
  // printf("%lld\n", my_pi);
  print_pi_digits (pi_digit_requested + 1);
  printf("\n");
}

long long
make_pi_digits (size_t count)
{
  size_t a_capacity = 1 + (10 * count) / 3;
  signed predigits[count];
  size_t predigits_size = 0;
  long long output = 0;
  signed A[a_capacity];
  // set array elems to 2
  for (size_t i = 0; i < a_capacity; ++i)
    {
      A[i] = 2;
    }

  for (size_t _ = count; _; --_)
    {
      A[a_capacity - 1] *= 10;
      for (size_t logical_i = a_capacity; logical_i > 1; --logical_i)
        {
          size_t ref_i = logical_i - 1;
          div_t qr = div (A[ref_i], 2 * logical_i - 1);
          A[ref_i] = qr.rem;
          A[ref_i - 1] = (A[ref_i - 1] * 10) + (logical_i - 1) * qr.quot;
        }
      div_t qr = div (A[0], 10);
      A[0] = qr.rem;
      switch (qr.quot)
        {
        case 9: predigits[predigits_size++] = qr.quot;
          break;
        case 10:
          for (size_t i = 0; i < predigits_size; ++i)
            {
              output = 10 * output + ((1 + predigits[i]) % 10);
            };
          predigits[0] = 0;
          predigits_size = 1;
          break;
        default:
          for (size_t i = 0; i < predigits_size; ++i)
            {
              output = 10 * output + predigits[i];
            };
          predigits[0] = qr.quot;
          predigits_size = 1;
        }
    }
  return output;
}

void
print_pi_digits (size_t count)
{
  size_t a_capacity = 1 + (10 * count) / 3;
  signed predigits[count];
  size_t predigits_size = 0;
  signed A[a_capacity];
  // set array elems to 2
  for (size_t i = 0; i < a_capacity; ++i)
    {
      A[i] = 2;
    }

  for (size_t _ = count; _; --_)
    {
      A[a_capacity - 1] *= 10;
      for (size_t logical_i = a_capacity; logical_i > 1; --logical_i)
        {
          size_t ref_i = logical_i - 1;
          div_t qr = div (A[ref_i], 2 * logical_i - 1);
          A[ref_i] = qr.rem;
          A[ref_i - 1] = (A[ref_i - 1] * 10) + (logical_i - 1) * qr.quot;
        }
      div_t qr = div (A[0], 10);
      A[0] = qr.rem;
      switch (qr.quot)
        {
        case 9: predigits[predigits_size++] = qr.quot;
          break;
        case 10:
          for (size_t i = 0; i < predigits_size; ++i)
            {
              fputc ('0' + (1 + predigits[i]) % 10, stdout);
            };
          fflush(stdout);
          predigits[0] = 0;
          predigits_size = 1;
          break;
        default:
          for (size_t i = 0; i < predigits_size; ++i)
            {
              fputc('0' + predigits[i], stdout);
            };
          fflush(stdout);
          predigits[0] = qr.quot;
          predigits_size = 1;
        }
    }
}
