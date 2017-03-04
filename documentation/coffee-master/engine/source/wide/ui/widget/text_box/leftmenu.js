function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6456\" class=\"headerLeftMenuInActive\"><a id=\"aID6456\" href=\"#\" OnMouseOver=\"link('_dir','text_box0',this)\" class=\"leftMenuLinkHeadInActive\">text_box</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1031\" class=\"leftMenuInActive\"><a id=\"aID1031\" href=\"#\" OnMouseOver=\"link('_class','TextBox45101',this)\" class=\"leftMenuLinkInActive\">TextBox</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6250\" class=\"leftMenuInActive\"><a id=\"aID6250\" href=\"#\" OnMouseOver=\"link('_member','TEXT_BOX_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">TEXT_BOX_STYLE</a></div>\n");
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
