function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6427\" class=\"headerLeftMenuInActive\"><a id=\"aID6427\" href=\"#\" OnMouseOver=\"link('_dir','file_dialog0',this)\" class=\"leftMenuLinkHeadInActive\">file_dialog</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID960\" class=\"leftMenuInActive\"><a id=\"aID960\" href=\"#\" OnMouseOver=\"link('_class','FileDialog49249',this)\" class=\"leftMenuLinkInActive\">FileDialog</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6233\" class=\"leftMenuInActive\"><a id=\"aID6233\" href=\"#\" OnMouseOver=\"link('_member','FILE_DIALOG_FLAG121877613',this)\" class=\"leftMenuLinkInActive\">FILE_DIALOG_FLAG</a></div>\n");
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
