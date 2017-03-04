function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6466\" class=\"headerLeftMenuInActive\"><a id=\"aID6466\" href=\"#\" OnMouseOver=\"link('_dir','window0',this)\" class=\"leftMenuLinkHeadInActive\">window</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6462\" class=\"leftMenuInActive\"><a id=\"aID6462\" href=\"#\" OnMouseOver=\"link('_dir','clip_board/clip_board0',this)\" class=\"leftMenuLinkInActive\">clip_board</a></div>\n");
document.write("<div id=\"divID6463\" class=\"leftMenuInActive\"><a id=\"aID6463\" href=\"#\" OnMouseOver=\"link('_dir','cursor/cursor0',this)\" class=\"leftMenuLinkInActive\">cursor</a></div>\n");
document.write("<div id=\"divID6464\" class=\"leftMenuInActive\"><a id=\"aID6464\" href=\"#\" OnMouseOver=\"link('_dir','drag_context/drag_context0',this)\" class=\"leftMenuLinkInActive\">drag_context</a></div>\n");
document.write("<div id=\"divID6465\" class=\"leftMenuInActive\"><a id=\"aID6465\" href=\"#\" OnMouseOver=\"link('_dir','layout/layout0',this)\" class=\"leftMenuLinkInActive\">layout</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1043\" class=\"leftMenuInActive\"><a id=\"aID1043\" href=\"#\" OnMouseOver=\"link('_class','DesktopWindow49249',this)\" class=\"leftMenuLinkInActive\">DesktopWindow</a></div>\n");
document.write("<div id=\"divID1044\" class=\"leftMenuInActive\"><a id=\"aID1044\" href=\"#\" OnMouseOver=\"link('_class','Window49249',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
document.write("<div id=\"divID1045\" class=\"leftMenuInActive\"><a id=\"aID1045\" href=\"#\" OnMouseOver=\"link('_class','WindowContext49249',this)\" class=\"leftMenuLinkInActive\">WindowContext</a></div>\n");
document.write("<div id=\"divID1046\" class=\"leftMenuInActive\"><a id=\"aID1046\" href=\"#\" OnMouseOver=\"link('_class','WindowManager49249',this)\" class=\"leftMenuLinkInActive\">WindowManager</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6255\" class=\"leftMenuInActive\"><a id=\"aID6255\" href=\"#\" OnMouseOver=\"link('_member','WINDOW_EVENT121877613',this)\" class=\"leftMenuLinkInActive\">WINDOW_EVENT</a></div>\n");
document.write("<div id=\"divID6256\" class=\"leftMenuInActive\"><a id=\"aID6256\" href=\"#\" OnMouseOver=\"link('_member','WINDOW_HIT_TYPE121877613',this)\" class=\"leftMenuLinkInActive\">WINDOW_HIT_TYPE</a></div>\n");
document.write("<div id=\"divID6257\" class=\"leftMenuInActive\"><a id=\"aID6257\" href=\"#\" OnMouseOver=\"link('_member','WINDOW_STATE121877613',this)\" class=\"leftMenuLinkInActive\">WINDOW_STATE</a></div>\n");
document.write("<div id=\"divID6258\" class=\"leftMenuInActive\"><a id=\"aID6258\" href=\"#\" OnMouseOver=\"link('_member','WINDOW_STYLE121877613',this)\" class=\"leftMenuLinkInActive\">WINDOW_STYLE</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
