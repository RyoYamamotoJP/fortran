module quicksort
    use iso_fortran_env, only: int64
    implicit none
    private

    interface sort
        module procedure isort, rsort
    end interface sort

    interface
        subroutine fquicksort(a, lo, hi, ip) bind(C)
            use iso_c_binding, only: c_float, c_size_t
            real(c_float), intent(inout) :: a(*)
            integer(c_size_t), value, intent(in) :: lo, hi
            integer(c_size_t), intent(inout) :: ip(*)
        end subroutine fquicksort

        subroutine iquicksort(a, lo, hi, ip) bind(C)
            use iso_c_binding, only: c_int, c_size_t
            integer(c_int), intent(inout) :: a(*)
            integer(c_size_t), value, intent(in) :: lo, hi
            integer(c_size_t), intent(inout) :: ip(*)
        end subroutine iquicksort
    end interface

    public :: sort
contains
    subroutine isort(array, index_array)
        integer, intent(inout) :: array(:)
        integer(int64), intent(out), optional :: index_array(:)
        integer :: n

        n = size(array)
        if (present(index_array)) index_array = iota(n)
        call iquicksort(array, int(0, int64), int(n - 1, int64), index_array)
    end subroutine isort

    subroutine rsort(array, index_array)
        real, intent(inout) :: array(:)
        integer(int64), intent(out), optional :: index_array(:)
        integer :: n

        n = size(array)
        if (present(index_array)) index_array = iota(n)
        call fquicksort(array, int(0, int64), int(n - 1, int64), index_array)
    end subroutine rsort

    pure function iota(n) result(a)
        integer, intent(in) :: n
        integer :: i
        integer(int64) :: a(n)

        do i = 1, n
            a(i) = i
        end do
    end function iota
end module quicksort
