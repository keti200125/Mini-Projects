using System;

namespace Space.Models
{
    public class Position
    {
        private int _row;
        private int _col;

        public int Row
        {
            get { return _row; }

            set
            {
                if (value < 0 || value > 100)
                {
                    throw new ArgumentOutOfRangeException(nameof(value), "Rows must be >= 0 and <= 100");
                }
                _row = value;
            }
        }
        public int Col
        {
            get { return _col; }

            set
            {
                if (value < 0 || value > 100)
                {
                    throw new ArgumentOutOfRangeException(nameof(value), "Columns must be >= 0 and <= 100");
                }
                _col = value;
            }
        }
        public Position(int row, int col)
        {
            Row = row;
            Col = col;
        }
    }
}
