module quicksort
    use, intrinsic :: iso_fortran_env, only: int64
    implicit none
    private

    interface sort
        module procedure isort, rsort
    end interface sort

    interface
        subroutine c_fsort(a, n, ip) bind(c, name='fsort')
            use, intrinsic :: iso_c_binding, only: c_float, c_size_t
            real(c_float), intent(inout) :: a(*)
            integer(c_size_t), value, intent(in) :: n
            integer(c_size_t), intent(inout) :: ip(*)
        end subroutine c_fsort

        subroutine c_isort(a, n, ip) bind(c, name='isort')
            use, intrinsic :: iso_c_binding, only: c_int32_t, c_size_t
            integer(c_int32_t), intent(inout) :: a(*)
            integer(c_size_t), value, intent(in) :: n
            integer(c_size_t), intent(inout) :: ip(*)
        end subroutine c_isort
    end interface

    public :: sort
contains
    subroutine isort(array, index_array)
        integer, intent(inout) :: array(:)
        integer(int64), intent(out), optional :: index_array(:)
        integer(int64) :: n

        n = size(array)
        call c_isort(array, n, index_array)
        if (present(index_array)) index_array = index_array + 1
    end subroutine isort

    subroutine rsort(array, index_array)
        real, intent(inout) :: array(:)
        integer(int64), intent(out), optional :: index_array(:)
        integer(int64) :: n

        n = size(array)
        call c_fsort(array, n, index_array)
        if (present(index_array)) index_array = index_array + 1
    end subroutine rsort
end module quicksort
