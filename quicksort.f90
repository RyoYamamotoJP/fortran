module quicksort
    implicit none
    private

    interface sort
        module procedure isort, rsort
    end interface sort

    interface
        subroutine fquicksort(a, lo, hi, ip) bind(C)
            use iso_c_binding, only: c_float, c_int
            real(c_float), intent(inout) :: a(*)
            integer(c_int), value, intent(in) :: lo, hi
            integer(c_int), intent(inout) :: ip(*)
        end subroutine fquicksort

        subroutine iquicksort(a, lo, hi, ip) bind(C)
            use iso_c_binding, only: c_int
            integer(c_int), intent(inout) :: a(*)
            integer(c_int), value, intent(in) :: lo, hi
            integer(c_int), intent(inout) :: ip(*)
        end subroutine iquicksort
    end interface

    public :: sort
contains
    subroutine isort(array, index_array)
        integer, intent(inout) :: array(:)
        integer, intent(out), optional :: index_array(:)
        integer :: n

        n = size(array)
        if (present(index_array)) index_array = iota(n)
        call iquicksort(array, 0, n - 1, index_array)
    end subroutine isort

    subroutine rsort(array, index_array)
        real, intent(inout) :: array(:)
        integer, intent(out), optional :: index_array(:)
        integer :: n

        n = size(array)
        if (present(index_array)) index_array = iota(n)
        call fquicksort(array, 0, n - 1, index_array)
    end subroutine rsort

    pure function iota(n) result(a)
        integer, intent(in) :: n
        integer :: i, a(n)

        do i = 1, n
            a(i) = i
        end do
    end function iota
end module quicksort
