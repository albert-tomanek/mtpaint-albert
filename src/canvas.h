/*	canvas.h
	Copyright (C) 2004-2009 Mark Tyler and Dmitry Groshev

	This file is part of mtPaint.

	mtPaint is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	mtPaint is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mtPaint in the file COPYING.
*/

float can_zoom;						// Zoom factor 1..MAX_ZOOM
int margin_main_x, margin_main_y,			// Top left of image from top left of canvas
	margin_view_x, margin_view_y;
int zoom_flag;
int marq_status, marq_x1, marq_y1, marq_x2, marq_y2;	// Selection marquee
int marq_drag_x, marq_drag_y;				// Marquee dragging offset
int line_status, line_x1, line_y1, line_x2, line_y2;	// Line tool
int poly_status;					// Polygon selection tool
int clone_x, clone_y;					// Clone offsets
int recent_files;					// Current recent files setting
int brush_spacing;					// Step in non-continuous mode


#define STATUS_ITEMS 5
#define STATUS_GEOMETRY 0
#define STATUS_CURSORXY 1
#define STATUS_PIXELRGB 2
#define STATUS_SELEGEOM 3
#define STATUS_UNDOREDO 4

GtkWidget *label_bar[STATUS_ITEMS];

int	col_reverse,					// Painting with right button
	show_paste,					// Show contents of clipboard while pasting
	status_on[STATUS_ITEMS],			// Show status bar items?
	text_paste,					// Are we pasting text?
	canvas_image_centre,				// Are we centering the image?
	chequers_optimize				// Are we optimizing the chequers for speed?
	;

#define LINE_NONE 0
#define LINE_START 1
#define LINE_LINE 2

#define MARQUEE_NONE 0
#define MARQUEE_SELECTING 1
#define MARQUEE_DONE 2
#define MARQUEE_PASTE 3
#define MARQUEE_PASTE_DRAG 4

#define POLY_NONE 0
#define POLY_SELECTING 1
#define POLY_DRAGGING 2
#define POLY_DONE 3

#define GRAD_NONE 0
#define GRAD_START 1
#define GRAD_END 2
#define GRAD_DONE 3

#define MIN_ZOOM 0.1
#define MAX_ZOOM 20

#define FS_PNG_LOAD 1		// File selector codes
#define FS_PNG_SAVE 2
#define FS_PALETTE_LOAD 3
#define FS_PALETTE_SAVE 4
#define FS_CLIP_FILE 5
#define FS_EXPORT_UNDO 6
#define FS_EXPORT_UNDO2 7
#define FS_EXPORT_ASCII 8
#define FS_LAYER_SAVE 9
#define FS_GIF_EXPLODE 10
#define FS_EXPORT_GIF 11
#define FS_CHANNEL_LOAD 12
#define FS_CHANNEL_SAVE 13
#define FS_COMPOSITE_SAVE 14
#define FS_SELECT_FILE 15
#define FS_SELECT_DIR 16
#define FS_LAYER_LOAD 17
#define FS_PATTERN_LOAD 18
#define FS_CLIPBOARD 19

#define FS_ENTRY_KEY "mtPaint.fs_entry"

int do_a_load( char *fname );
void align_size( float new_zoom );
int alert_box( char *title, char *message, char *text1, char *text2, char *text3 );
void init_ls_settings(ls_settings *settings, GtkWidget *box);
void fs_setup(GtkWidget *fs, int action_type);
void file_selector( int action_type );
void init_pal();			// Initialise palette after loading/palette changes
void update_cols();
void set_new_filename(int layer, char *fname);

void main_undo();
void main_redo();

void choose_pattern();					// Bring up pattern chooser
void tool_action(int event, int x, int y, int button, gdouble pressure);	// Paint some pixels!
void update_menus();					// Update undo/edit menu

int close_to( int x1, int y1 );

void get_visible(int *vxy);

void paint_marquee(int action, int new_x, int new_y);	// Draw/clear marquee
void refresh_marquee(rgbcontext *ctx);			// Refresh a part of marquee
void paint_poly_marquee(rgbcontext *ctx, int whole);	// Paint polygon marquee
void stretch_poly_line(int x, int y);			// Clear old temp line, draw next temp line

void update_sel_bar();			// Update selection stats on status bar
void update_xy_bar(int x, int y);	// Update cursor tracking on status bar
void init_status_bar();			// Initialize status bar

void pressed_lasso(int cut);
void pressed_copy(int cut);
void pressed_paste(int centre);
void pressed_greyscale(int mode);
void pressed_convert_rgb();
void pressed_invert();
void pressed_rectangle(int filled);
void pressed_ellipse(int filled);

void pressed_edge_detect();
void pressed_sharpen();
void pressed_soften();
void pressed_fx(int what);
void pressed_gauss();
void pressed_unsharp();
void pressed_dog();
void pressed_kuwahara();

void pressed_clip_alpha_scale();
void pressed_clip_alphamask();
void pressed_clip_mask(int val);
void pressed_clip_mask_all();
void pressed_clip_mask_clear();

void pressed_flip_image_v();
void pressed_flip_image_h();
void pressed_flip_sel_v();
void pressed_flip_sel_h();

void pressed_rotate_image(int dir);
void pressed_rotate_sel(int dir);
void pressed_rotate_free();

void iso_trans(int mode);

void update_paste_chunk( int x1, int y1, int x2, int y2 );
void check_marquee();
void commit_paste(int swap, int *update);

void trace_line(int mode, int lx1, int ly1, int lx2, int ly2, int *vxy, rgbcontext *ctx);
void repaint_line(int mode);			// Repaint or clear line on canvas
void repaint_grad(int mode);			// Same for gradient line
void refresh_grad(rgbcontext *ctx);		// Refresh a part of gradient line
void register_file( char *filename );		// Called after successful load/save
void update_recent_files();			// Update the menu items

void scroll_wheel( int x, int y, int d );	// Scroll wheel action from mouse

void update_all_views();			// Update whole canvas on all views

void create_default_image();			// Create default new image

/// UPDATE STUFF

/* Atomic updates */

#define CF_NAME   0x00000001 /* Name in titlebar */
#define CF_GEOM   0x00000002 /* Image geometry */
#define CF_CGEOM  0x00000004 /* Clipboard geometry */
#define CF_PAL    0x00000008 /* Palette */
#define CF_CAB    0x00000010 /* Current channel's A & B (w/redraw) */
#define CF_AB     0x00000020 /* Colors A & B */
#define CF_GRAD   0x00000040 /* Gradients */
#define CF_MENU   0x00000080 /* Menus and controls */
#define CF_SET    0x00000100 /* Settings toolbar */
#define CF_IMGBAR 0x00000200 /* Image statusbar */
#define CF_SELBAR 0x00000400 /* Selection statusbar */
#define CF_PIXEL  0x00000800 /* Pixel statusbar */
#define CF_PREFS  0x00001000 /* Preferences */
#define CF_CURSOR 0x00002000 /* Cursor */
#define CF_PMODE  0x00004000 /* Paste preview */
#define CF_GMODE  0x00008000 /* Gradient preview */
#define CF_DRAW   0x00010000 /* Image window */
#define CF_VDRAW  0x00020000 /* View window */
#define CF_PDRAW  0x00040000 /* Palette window */
#define CF_TDRAW  0x00080000 /* Color/brush/pattern window */
#define CF_ALIGN  0x00100000 /* Realign image window */
#define CF_VALIGN 0x00200000 /* Realign view window */

/* Compound updates */

//	Changed image contents
#define UPD_IMG    (CF_DRAW | CF_VDRAW | CF_PIXEL)
//	Changed image geometry (+undo)
#define UPD_GEOM   (CF_GEOM | CF_MENU | CF_IMGBAR | UPD_IMG)
//	Added a new channel (+)
#define UPD_ADDCH  (CF_MENU | CF_IMGBAR | UPD_IMG)
//	Deleted an existing channel (+)
#define UPD_DELCH  UPD_ADDCH
//	Switched to new channel (+)
#define UPD_NEWCH  (UPD_ADDCH | UPD_CAB | CF_SELBAR)
//	Switched to existing channel
#define UPD_CHAN   UPD_NEWCH /* May avoid view window redraw, but won't bother */
//	Changed color or value A or B
#define UPD_CAB    CF_CAB
//	Changed color A or B
#define UPD_AB     (CF_AB | CF_GRAD | CF_SET | CF_GMODE | CF_TDRAW)
//	Changed pattern
#define UPD_PAT    (CF_AB | CF_TDRAW)
//	Changed A, B, and pattern
#define UPD_ABP    UPD_AB
//	Changed palette 
#define UPD_PAL    (CF_PAL | CF_IMGBAR | CF_PDRAW | UPD_AB | UPD_IMG)
//	Added colors to palette
#define UPD_ADDPAL (CF_PAL | CF_IMGBAR | CF_PDRAW)
//	Changed drawing mode in some way
#define UPD_MODE   (CF_PMODE | CF_GMODE)
//	Toggled gradient mode
#define UPD_GMODE  CF_DRAW
//	Changed palette if indexed / image if RGB
#define UPD_COL    UPD_PAL /* May avoid palette update for RGB, but... */
//	Changed image contents (+undo, -redraw)
#define UPD_IMGP   (CF_MENU | CF_PIXEL)
//	Copied selection to clipboard
#define UPD_COPY   CF_MENU
//	Imported clipboard
#define UPD_XCOPY  CF_MENU
//	Converted indexed image to RGB
#define UPD_2RGB   (CF_MENU | CF_IMGBAR | UPD_IMG)
//	Converted RGB image to indexed
#define UPD_2IDX   (UPD_2RGB | UPD_PAL)
//	Created or loaded a new image (+)
#define UPD_ALL    (UPD_GEOM | UPD_PAL | UPD_CAB)
//	Changed clipboard contents
#define UPD_CLIP   CF_PMODE
//	Changed rendering options
#define UPD_RENDER CF_DRAW
//	Changed clipboard geometry
#define UPD_CGEOM  (CF_CGEOM | CF_SELBAR | UPD_CLIP)
//	Changed polygonal selection
#define UPD_PSEL   (CF_MENU | CF_SELBAR)
//	Changed selection
#define UPD_SEL    (UPD_PSEL | CF_CURSOR)
//	Changed selection geometry
#define UPD_SGEOM  UPD_PSEL
//	Initiated pasting something
#define UPD_PASTE  (UPD_SEL | CF_DRAW)
//	Changed filename
#define UPD_NAME   CF_NAME
//	Changed transparent color
#define UPD_TRANS  (UPD_IMG | CF_IMGBAR)
//	Changed image contents (+undo)
#define UPD_UIMG   (UPD_IMG | CF_MENU)
//	Cut selection
#define UPD_CUT    UPD_UIMG
//	Switched layers
#define UPD_LAYER  (UPD_ALL | CF_NAME | CF_VALIGN)
//	Changed color masking
#define UPD_CMASK  (CF_PDRAW | UPD_MODE)
//	Changed tool opacity
#define UPD_OPAC   (CF_GRAD | CF_SET | UPD_MODE)
//	Done "reset tools" (in addition to UPD_ALL)
#define UPD_RESET  (CF_NAME | CF_ALIGN | UPD_PAL | UPD_OPAC)
//	Changed brush
#define UPD_BRUSH  (CF_SET | CF_CURSOR | CF_TDRAW)
//	Changed gradient
#define UPD_GRAD   (CF_GRAD | CF_SET | CF_GMODE)
//	Changed preferences
#define UPD_PREFS  (CF_PREFS | CF_MENU | CF_CURSOR | CF_DRAW | CF_VDRAW)
//	Moved color in palette (no image redraw desired)
#define UPD_MVPAL  (UPD_PAL & ~UPD_IMG)
//	Mask covering all kinds of image redraw - for disabling them
#define UPD_IMGMASK (UPD_MODE | CF_DRAW | CF_VDRAW)
// !!! Do not forget: CF_MENU also tracks undo stack changes

void update_stuff(int flags);
