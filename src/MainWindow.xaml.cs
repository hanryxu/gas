using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace gas
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_ContentRendered(object sender, EventArgs e)
        {
            DrawCity();
            StartGame();
        }

        private void DrawCity()
        {
            City.Width = SquareSize * Column;
            City.Height = SquareSize * Row;
            bool doneDrawingBackground = false;
            int nextR = 0, nextC = 0;
            bool nextIsOdd = false;
            while (doneDrawingBackground == false)
            {
                Rectangle rect = new Rectangle
                {
                    Width = SquareSize,
                    Height = SquareSize,
                    Fill = nextIsOdd ? Brushes.White : Brushes.Black
                };
                City.Children.Add(rect);
                Canvas.SetTop(rect, nextR * SquareSize);
                Canvas.SetLeft(rect, nextC * SquareSize);

                nextIsOdd = !nextIsOdd;
                nextC++;
                if (nextC >= City.ActualWidth)
                {
                    nextC = 0;
                    nextR++;
                    nextIsOdd = (nextR % 2 != 0);
                }

                if (nextR >= Row)
                    doneDrawingBackground = true;
            }
        }

        private int Row = 8, Column = 8;

        const int SquareSize = 20;
        const int health = 12;

        private SolidColorBrush FlatulanBrush = Brushes.Brown;
        private SolidColorBrush PlayerBrush = Brushes.Red;
        private List<Flatulan> Flatulans = new List<Flatulan>();
        public enum Direction { Left, Right, Up, Down };

        private Random rnd = new Random();

        public class Flatulan
        {
            public Point Position { get; set; }
            public bool ToDelete;
        }

        public class Player
        {
            public Point Position { get; set; }
            public UIElement UiElement { get; set; }
            public int Age = 0;
            public int cntGassed = 0;
        }

        Player player = new Player();

        private void DrawFlatulans()
        {
            int[,] numGrid = new int[Row, Column];
            foreach (Flatulan flatulan in Flatulans)
            {
                int frow = (int)(flatulan.Position.Y / SquareSize);
                int fcol = (int)(flatulan.Position.X / SquareSize);
                numGrid[frow, fcol]++;
            }
            var TextBoxs = City.Children.OfType<TextBox>().ToList();
            foreach (var TB in TextBoxs)
                City.Children.Remove(TB);
            for (int i = 0; i < Row; i++)
                for (int j = 0; j < Column; j++)
                    if (numGrid[i, j] != 0)
                    {
                        TextBox numGird = new TextBox()
                        {
                            Width = SquareSize,
                            Height = SquareSize,
                            Text = numGrid[i, j].ToString(),
                            TextAlignment = TextAlignment.Center
                        };
                        City.Children.Add(numGird);
                        Canvas.SetTop(numGird, i * SquareSize);
                        Canvas.SetLeft(numGird, j * SquareSize);
                    }
        }

        private void DrawPlayer()
        {
            City.Children.Remove(player.UiElement);
            player.UiElement = new Rectangle()
            {
                Width = SquareSize,
                Height = SquareSize,
                Fill = PlayerBrush
            };
            City.Children.Add(player.UiElement);
            Canvas.SetTop(player.UiElement, player.Position.Y);
            Canvas.SetLeft(player.UiElement, player.Position.X);
        }

        private void DrawEverything()
        {
            DrawPlayer();
            DrawFlatulans();
        }

        private int nFlatulansAt(Point pos)
        {
            int cnt = 0;
            foreach (Flatulan flatulan in Flatulans)
                if (flatulan.Position == pos)
                    cnt++;
            return cnt;
        }

        private void MovePlayer(Direction dir)
        {
            player.Age++;
            Point tar = player.Position;
            MoveAnything(ref tar, dir);
            if (nFlatulansAt(tar) == 0)
                player.Position = tar;
        }

        private void MoveAnything(ref Point point, Direction dir)
        {
            switch (dir)
            {
                case Direction.Left:
                    if (isInBounds(new Point(point.X - SquareSize, point.Y)))
                        point.X -= SquareSize;
                    break;
                case Direction.Right:
                    if (isInBounds(new Point(point.X + SquareSize, point.Y)))
                        point.X += SquareSize;
                    break;
                case Direction.Up:
                    if (isInBounds(new Point(point.X, point.Y - SquareSize)))
                        point.Y -= SquareSize;
                    break;
                case Direction.Down:
                    if (isInBounds(new Point(point.X, point.Y + SquareSize)))
                        point.Y += SquareSize;
                    break;
            }
        }

        private bool isInBounds(Point point)
        {
            int r = (int)(point.Y / SquareSize), c = (int)(point.X / SquareSize);
            if (r >= 0 && r < Row && c >= 0 && c < Column)
                return true;
            return false;
        }

        private void MoveFlatulans()
        {
            foreach (Flatulan flatulan in Flatulans)
            {
                Direction dir = (Direction)rnd.Next(0, 4);

                Point tar = flatulan.Position;
                MoveAnything(ref tar, dir);
                if (player.Position != tar)
                    flatulan.Position = tar;
                bool ifUp = ((flatulan.Position.X == player.Position.X) && (flatulan.Position.Y == player.Position.Y - SquareSize));
                bool ifDown = ((flatulan.Position.X == player.Position.X) && (flatulan.Position.Y == player.Position.Y + SquareSize));
                bool ifLeft = ((flatulan.Position.X == player.Position.X - SquareSize) && (flatulan.Position.Y == player.Position.Y));
                bool ifRight = ((flatulan.Position.X == player.Position.X + SquareSize) && (flatulan.Position.Y == player.Position.Y));
                if (ifUp || ifDown || ifLeft || ifRight)
                    player.cntGassed++;
            }

            DrawEverything();

            if (Flatulans.Count == 0)
                Win();
            if (health - player.cntGassed <= 0)
                Lose();
        }

        private void Preach()
        {
            foreach (Flatulan flatulan in Flatulans)
            {
                flatulan.ToDelete = false;
                bool ifX = ((flatulan.Position.X >= player.Position.X - SquareSize) && (flatulan.Position.X <= player.Position.X + SquareSize));
                bool ifY = ((flatulan.Position.Y >= player.Position.Y - SquareSize) && (flatulan.Position.Y <= player.Position.Y + SquareSize));
                if (ifX && ifY)
                {
                    int converted = rnd.Next(0, 3);
                    if (converted != 2)
                        flatulan.ToDelete = true;
                }
            }
            Flatulans.RemoveAll((Flatulan => Flatulan.ToDelete == true));
        }

        private void addFlatulans()
        {
            int addRow = rnd.Next(0, Row);
            int addCol = rnd.Next(0, Column);
            if (player.Position.X == addCol * SquareSize && player.Position.Y == addRow * SquareSize)
                addFlatulans();
            else
            {
                Point addPoint = new Point()
                {
                    X = addCol * SquareSize,
                    Y = addRow * SquareSize
                };
                Flatulans.Add(new Flatulan()
                {
                    Position = addPoint
                });
            }
        }

        private void addPlayer()
        {
            int addRow = rnd.Next(0, Row);
            int addCol = rnd.Next(0, Column);
            Point addPoint = new Point()
            {
                X = addCol * SquareSize,
                Y = addRow * SquareSize
            };
            player.Position = addPoint;
            player.UiElement = null;
            player.Age = 0;
            player.cntGassed = 0;
        }

        private void Window_KeyUp(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Up:
                    MovePlayer(Direction.Up);
                    break;
                case Key.Down:
                    MovePlayer(Direction.Down);
                    break;
                case Key.Left:
                    MovePlayer(Direction.Left);
                    break;
                case Key.Right:
                    MovePlayer(Direction.Right);
                    break;
                case Key.Enter:
                    Preach();
                    break;
                case Key.Escape:
                    this.Close();
                    break;
            }
            MoveFlatulans();
        }

        private void StartGame()
        {
            addPlayer();
            for (int i = 0; i <= 9; i++)
                addFlatulans();
            DrawEverything();
        }

        private void Win()
        {
            MessageBox.Show("You WIN! With " + (health - player.cntGassed).ToString() + " health remaining, and lasted for " + player.Age.ToString() + " rounds");
            StartGame();
        }
        private void Lose()
        {
            MessageBox.Show("You lose, and you lasted for " + player.Age.ToString() + " rounds.");
            StartGame();
        }
    }
}
