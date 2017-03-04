function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6430\" class=\"headerLeftMenuInActive\"><a id=\"aID6430\" href=\"#\" OnMouseOver=\"link('_dir','rename_box0',this)\" class=\"leftMenuLinkHeadInActive\">rename_box</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID963\" class=\"leftMenuInActive\"><a id=\"aID963\" href=\"#\" OnMouseOver=\"link('_class','RenameBox49249',this)\" class=\"leftMenuLinkInActive\">RenameBox</a></div>\n");
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
